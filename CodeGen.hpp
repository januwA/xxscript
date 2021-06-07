#pragma once

#include <iostream>
#include <format>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>

#include "KaleidoscopeJIT.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"

#include "ast.hpp"
#include "parser.h"

using namespace llvm;
using namespace llvm::orc;

namespace xxs
{

  struct CodeGen
  {
    std::unique_ptr<LLVMContext> ctx;
    std::unique_ptr<IRBuilder<>> builder;
    std::unique_ptr<Module> m;
    std::unique_ptr<legacy::FunctionPassManager> fmp;
    std::map<std::string, Value *> Variables;
    CodeGen()
    {
      ctx = std::make_unique<LLVMContext>();
      InitializeModuleAndPassManager();
      builder = std::make_unique<IRBuilder<>>(*ctx);
    }

    void init_main(xxs::FunctionAst *_main)
    {
      auto ftype = FunctionType::get(Type::getInt32Ty(*ctx), {}, false);
      auto main_fun = Function::Create(ftype, Function::ExternalLinkage, "__main", m.get());
      BasicBlock *BB = BasicBlock::Create(*ctx, "entry", main_fun);
      builder->SetInsertPoint(BB);
      codegen(_main->body);
      fmp->run(*main_fun);
    }

    void InitializeModuleAndPassManager()
    {
      m = std::make_unique<Module>("jit", *ctx);

      // 创建一个优化器，附加到模块
      fmp = std::make_unique<legacy::FunctionPassManager>(m.get());

      // Do simple "peephole" optimizations and bit-twiddling optzns.
      fmp->add(createInstructionCombiningPass());
      // Reassociate expressions.
      fmp->add(createReassociatePass());
      // Eliminate Common SubExpressions.
      fmp->add(createGVNPass());
      // Simplify the control flow graph (deleting unreachable blocks, etc).
      fmp->add(createCFGSimplificationPass());

      fmp->doInitialization();
    }

    Value *codegen(PAST ast)
    {
      switch (ast->id())
      {
      case AT::Int:
        return cg_int(reinterpret_cast<IntAst *>(ast));
      case AT::Float:
        return cg_float(reinterpret_cast<FloatAst *>(ast));
      case AT::VarAccess:
        return cg_varAccess(reinterpret_cast<VarAccessAst *>(ast));
      case AT::Binary:
        return cg_binary(reinterpret_cast<BinaryAst *>(ast));
      case AT::Call:
        return cg_call(reinterpret_cast<CallAst *>(ast));
      case AT::Function:
        return cg_function(reinterpret_cast<FunctionAst *>(ast));
      case AT::Block:
        return cg_block(reinterpret_cast<BlockAst *>(ast));
      case AT::Ret:
        return cg_ret(reinterpret_cast<RetAst *>(ast));
      }
    }

    void print()
    {
      m->print(errs(), nullptr);
    }

  private:
    Value *cg_int(IntAst *ast)
    {
      return builder->getInt32(ast->num);
    }
    Value *cg_float(FloatAst *ast)
    {
      return ConstantFP::get(*ctx, APFloat(ast->num));
    }
    Value *cg_varAccess(VarAccessAst *ast)
    {
      return Variables.count(ast->name) ? Variables[ast->name] : builder->getInt32(0);
    }
    Value *cg_binary(BinaryAst *ast)
    {
      auto l = codegen(ast->left);
      auto r = codegen(ast->right);
      switch (ast->op)
      {
      case parser::token::PLUS:
        return builder->CreateAdd(l, r);
      case parser::token::MINUS:
        return builder->CreateSub(l, r);
      case parser::token::MUL:
        return builder->CreateMul(l, r);
      case parser::token::DIV:
        return builder->CreateExactSDiv(l, r);
      case parser::token::LT:
        return builder->CreateICmpSLT(l, r);
      case parser::token::GT:
        return builder->CreateICmpSGT(l, r);
      case parser::token::LTE:
        return builder->CreateICmpSLE(l, r);
      case parser::token::GTE:
        return builder->CreateICmpSGE(l, r);
      case parser::token::EE:
        return builder->CreateICmpEQ(l, r);
      case parser::token::NE:
        return builder->CreateICmpNE(l, r);
      default:
        break;
      }
    }
    Value *cg_call(CallAst *ast)
    {
      Function *fun = reinterpret_cast<Function *>(codegen(ast->name));
      if (fun->arg_size() != ast->args.size())
      {
        throw std::exception(std::format("'{}' 参数数量错误.", fun->getName().str()).data());
      }

      std::vector<Value *> argv;
      for (auto a : ast->args)
      {
        argv.push_back(codegen(a));
      }
      return builder->CreateCall(fun, argv);
    }

    Value *cg_function(FunctionAst *ast)
    {
      auto parentBB = builder->GetInsertBlock();

      auto fname = ast->name;
      auto params = ast->params;
      std::vector<Type *> fparams(params.size(), Type::getInt32Ty(*ctx));
      auto ftype = FunctionType::get(Type::getInt32Ty(*ctx), fparams, false);
      auto fun = Function::Create(ftype, Function::ExternalLinkage, fname, m.get());

      BasicBlock *BB = BasicBlock::Create(*ctx, "entry", fun);
      builder->SetInsertPoint(BB);

      // set arg name
      int i = 0;
      for (auto &arg : fun->args())
        arg.setName(params[i++]);

      Variables[fname] = fun;

      for (auto &Arg : fun->args())
        Variables[Arg.getName().str()] = &Arg;
      codegen(ast->body);
      verifyFunction(*fun);

      builder->SetInsertPoint(parentBB);
      
      // 为函数添加优化器
      fmp->run(*fun);

      return fun;
    }

    Value *cg_block(BlockAst *ast)
    {
      auto BB = builder->GetInsertBlock();
      builder->SetInsertPoint(BB);
      for (auto s : ast->blocks)
      {
        codegen(s);
      }
      return BB;
    }
    
    Value *cg_ret(RetAst *ast)
    {
      return builder->CreateRet(ast->val ? codegen(ast->val) : builder->getInt32(0));
    }
  };

}
