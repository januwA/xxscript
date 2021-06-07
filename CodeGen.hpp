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

namespace xxs
{

  struct CodeGen
  {
    std::unique_ptr<LLVMContext> ctx;
    std::unique_ptr<IRBuilder<>> b;
    std::unique_ptr<Module> m;
    std::unique_ptr<legacy::FunctionPassManager> fmp;
    std::map<std::string, Value *> Variables;
    CodeGen()
    {
      ctx = std::make_unique<LLVMContext>();
      InitializeModuleAndPassManager();
      b = std::make_unique<IRBuilder<>>(*ctx);
    }

    void init_main(FunctionAst *_main)
    {
      auto ftype = FunctionType::get(Type::getInt32Ty(*ctx), {}, false);
      auto main_fun = Function::Create(ftype, Function::ExternalLinkage, "__main", m.get());
      cg_stmts(_main->body, main_fun);
      // fmp->run(*main_fun);
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

    Value *codegen(ast_ptr ast)
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
      case AT::Ret:
        return cg_ret(reinterpret_cast<RetAst *>(ast));
      case AT::If:
        return cg_if(reinterpret_cast<IfAst *>(ast));
      }
    }

    void print()
    {
      m->print(errs(), nullptr);
    }

  private:
    Value *cg_int(IntAst *ast)
    {
      return b->getInt32(ast->num);
    }

    Value *cg_float(FloatAst *ast)
    {
      return ConstantFP::get(*ctx, APFloat(ast->num));
    }

    Value *cg_varAccess(VarAccessAst *ast)
    {
      return Variables.count(ast->name) ? Variables[ast->name] : b->getInt32(0);
    }

    Value *cg_binary(BinaryAst *ast)
    {
      auto l = codegen(ast->left);
      auto r = codegen(ast->right);
      switch (ast->op)
      {
      case parser::token::PLUS:
        return b->CreateAdd(l, r);
      case parser::token::MINUS:
        return b->CreateSub(l, r);
      case parser::token::MUL:
        return b->CreateMul(l, r);
      case parser::token::DIV:
        return b->CreateExactSDiv(l, r);
      case parser::token::LT:
        return b->CreateICmpSLT(l, r);
      case parser::token::GT:
        return b->CreateICmpSGT(l, r);
      case parser::token::LTE:
        return b->CreateICmpSLE(l, r);
      case parser::token::GTE:
        return b->CreateICmpSGE(l, r);
      case parser::token::EE:
        return b->CreateICmpEQ(l, r);
      case parser::token::NE:
        return b->CreateICmpNE(l, r);
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
      return b->CreateCall(fun, argv);
    }

    Value *cg_function(FunctionAst *ast)
    {
      auto parentBB = b->GetInsertBlock();

      auto fname = ast->name;
      auto params = ast->params;
      std::vector<Type *> fparams(params.size(), Type::getInt32Ty(*ctx));
      auto ftype = FunctionType::get(Type::getInt32Ty(*ctx), fparams, false);
      auto fun = Function::Create(ftype, Function::ExternalLinkage, fname, m.get());

      // set arg name
      int i = 0;
      for (auto &arg : fun->args())
        arg.setName(params[i++]);

      Variables[fname] = fun;

      for (auto &Arg : fun->args())
        Variables[Arg.getName().str()] = &Arg;

      cg_stmts(ast->body, fun);

      verifyFunction(*fun);

      b->SetInsertPoint(parentBB);

      // 为函数添加优化器
      // fmp->run(*fun);

      return fun;
    }

    llvm::BasicBlock *cg_stmts(StmtsAst *ast, Function *parent, std::string_view name = "stmts")
    {
      auto BB = BasicBlock::Create(*ctx, name.data(), parent);
      b->SetInsertPoint(BB);
      for (auto s : ast->stmts)
      {
        codegen(s);
      }
      return BB;
    }

    llvm::BasicBlock *cg_stmts(StmtsAst *ast, BasicBlock *BB)
    {
      b->SetInsertPoint(BB);
      for (auto s : ast->stmts)
      {
        codegen(s);
      }
      return BB;
    }

    Value *cg_if(IfAst *ast)
    {
      // 获取正在构建的function
      auto f = b->GetInsertBlock()->getParent();

      auto MergeBB = BasicBlock::Create(*ctx, "merge", f);
      auto ThenBB = BasicBlock::Create(*ctx, "then", f);
      auto ElseBB = BasicBlock::Create(*ctx, "else", f);

      b->CreateCondBr(codegen(ast->cond), ThenBB, ElseBB);

      cg_stmts(ast->th, ThenBB);

      // 执行完cg_stmts后block point可能发生改变
      // 需要无条件跳回来
      b->CreateBr(MergeBB); 


      // ThenBB = Builder.GetInsertBlock();
      // f->getBasicBlockList().push_back(ElseBB);

      cg_stmts(ast->el, ElseBB);
      b->CreateBr(MergeBB);

      b->SetInsertPoint(MergeBB);
      return b->getInt1(0);
    }

    Value *cg_ret(RetAst *ast)
    {
      return b->CreateRet(ast->val ? codegen(ast->val) : b->getInt32(0));
    }
  };

}
