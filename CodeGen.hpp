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
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/ADT/Optional.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"

// JIT
#include "KaleidoscopeJIT.h"

#include "ast.hpp"
#include "parser.h"
#include "context.hpp"

using namespace llvm;
using namespace llvm::sys;
using namespace llvm::orc;

ExitOnError ExitOnErr;

namespace xxs
{
  struct CodeGen
  {
    std::unique_ptr<LLVMContext> llctx;
    std::unique_ptr<IRBuilder<>> b;
    std::unique_ptr<Module> m;
    std::unique_ptr<legacy::FunctionPassManager> fmp;
    xxs::Context ctx;

    BasicBlock *breakBB{nullptr};
    BasicBlock *continueBB{nullptr};
    bool bPass{false};

    CodeGen(bool bPass) : bPass(bPass)
    {
      llctx = std::make_unique<LLVMContext>();
      InitializeModuleAndPassManager();
      b = std::make_unique<IRBuilder<>>(*llctx);
    }

    // 声明外部函数
    void declares()
    {
      auto print = Function::Create(FunctionType::get(b->getInt64Ty(), {b->getInt64Ty(), b->getInt8PtrTy()}, true), Function::ExternalLinkage, "print", m.get());
      ctx.setf("print", print);

      auto llval2str1 = Function::Create(FunctionType::get(b->getInt8PtrTy(), {b->getInt64Ty()}, false), Function::ExternalLinkage, "llval2str", m.get());
    }

    int jit()
    {
      InitializeNativeTarget();
      InitializeNativeTargetAsmPrinter();
      InitializeNativeTargetAsmParser();

      auto JIT = ExitOnErr(KaleidoscopeJIT::Create());
      auto RT = JIT->getMainJITDylib().createResourceTracker();
      auto TSM = ThreadSafeModule(std::move(m), std::move(llctx));
      JIT->addModule(std::move(TSM), RT);
      auto ExprSymbol = ExitOnErr(JIT->lookup("main"));
      int (*FP)() = (int (*)())(intptr_t)ExprSymbol.getAddress();
      auto val = FP();
      ExitOnErr(RT->remove());
      return val;
    }

    void InitializeModuleAndPassManager()
    {
      m = std::make_unique<Module>("jit", *llctx);

      // 创建一个优化器，附加到模块
      fmp = std::make_unique<legacy::FunctionPassManager>(m.get());

      if (bPass)
      {
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
    }

    // https://releases.llvm.org/12.0.0/docs/tutorial/MyFirstLanguageFrontend/LangImpl08.html
    int aob()
    {
      InitializeAllTargetInfos();
      InitializeAllTargets();
      InitializeAllTargetMCs();
      InitializeAllAsmParsers();
      InitializeAllAsmPrinters();

      // 返回当前机器的目标三元组
      auto TargetTriple = sys::getDefaultTargetTriple();

      // 使用目标三元组来获得Target
      std::string Error;
      auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);

      if (!Target)
      {
        errs() << Error;
        return 1;
      }

      // 目标机器
      auto CPU = "generic";
      auto Features = "";

      TargetOptions opt;
      auto RM = Optional<Reloc::Model>();
      auto TargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

      // 配置模块，以指定目标和数据布局
      m->setDataLayout(TargetMachine->createDataLayout());
      m->setTargetTriple(TargetTriple);

      // 发出目标代码
      auto Filename = "output.o";
      std::error_code EC;
      raw_fd_ostream dest(Filename, EC, sys::fs::OF_None);

      if (EC)
      {
        errs() << "Could not open file: " << EC.message();
        return 1;
      }

      legacy::PassManager pass;
      auto FileType = CGFT_ObjectFile;

      if (TargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType))
      {
        errs() << "TargetMachine can't emit a file of this type";
        return 1;
      }

      if (bPass)
        pass.run(*m);
      dest.flush();
    }

    Value *codegen(ast_ptr ast)
    {
      switch (ast->id())
      {
      case AT::Int:
        return cg_int(reinterpret_cast<IntAst *>(ast));
      case AT::Float:
        return cg_float(reinterpret_cast<FloatAst *>(ast));
      case AT::Str:
        return cg_string(reinterpret_cast<StrAst *>(ast));
      case AT::VarAccess:
        return cg_varAccess(reinterpret_cast<VarAccessAst *>(ast));
      case AT::Binary:
        return cg_binary(reinterpret_cast<BinaryAst *>(ast));
      case AT::Call:
        return cg_call(reinterpret_cast<CallAst *>(ast));
      case AT::Function:
        return cg_function(reinterpret_cast<FuncAst *>(ast));
      case AT::Ret:
        return cg_ret(reinterpret_cast<RetAst *>(ast));
      case AT::If:
        return cg_if(reinterpret_cast<IfAst *>(ast));
      case AT::For:
        return cg_for(reinterpret_cast<ForAst *>(ast));
      case AT::VarAssign:
        return cg_varAssign(reinterpret_cast<VarAssignAst *>(ast));
      case AT::Stmts:
        return cg_stmts(reinterpret_cast<StmtsAst *>(ast));
      case AT::Break:
        return cg_break(reinterpret_cast<BreakAst *>(ast));
      case AT::Continue:
        return cg_continue(reinterpret_cast<ContinueAst *>(ast));
      case AT::List:
        return cg_list(reinterpret_cast<ListAst *>(ast));
      }
    }

    void print()
    {
      m->print(outs(), nullptr);
    }

  private:
    Value *cg_int(IntAst *ast)
    {
      return b->getInt64(ast->num);
    }

    Value *cg_float(FloatAst *ast)
    {
      return ConstantFP::get(*llctx, APFloat(ast->num));
    }

    Value *cg_string(StrAst *ast)
    {
      return b->CreateGlobalString(ast->str);
    }

    Value *cg_varAccess(VarAccessAst *ast)
    {
      auto *aa = ctx.get(ast->name);
      if (aa)
      {
        // printf("var:%s\n", ast->name);
        return b->CreateLoad(aa, ast->name);
      }

      auto fun = ctx.getf(ast->name);
      if (fun)
      {
        // printf("fun:%s\n", ast->name);
        return fun;
      }

      // printf("def:%s\n", ast->name);
      return b->getInt64(0);
    }

    Value *cg_binary(BinaryAst *ast)
    {
      auto l = codegen(ast->left);
      auto r = codegen(ast->right);
      switch (ast->op)
      {
      case parser::token::PLUS:
        if (isa<ConstantFP>(l) || isa<ConstantFP>(r))
          return b->CreateFAdd(b->CreateSIToFP(l, b->getDoubleTy()), b->CreateSIToFP(r, b->getDoubleTy()));
        else
          return b->CreateAdd(l, r);
      case parser::token::MINUS:
        if (isa<ConstantFP>(l) || isa<ConstantFP>(r))
          return b->CreateFSub(b->CreateSIToFP(l, b->getDoubleTy()), b->CreateSIToFP(r, b->getDoubleTy()));
        else
          return b->CreateSub(l, r);
      case parser::token::MUL:
        if (isa<ConstantFP>(l) || isa<ConstantFP>(r))
          return b->CreateFMul(b->CreateSIToFP(l, b->getDoubleTy()), b->CreateSIToFP(r, b->getDoubleTy()));
        else
          return b->CreateMul(l, r);

        // TODO: 5 / 2 => 2.5
      case parser::token::DIV:
        if (isa<ConstantFP>(l) || isa<ConstantFP>(r))
          return b->CreateFDiv(b->CreateSIToFP(l, b->getDoubleTy()), b->CreateSIToFP(r, b->getDoubleTy()));
        else
          return b->CreateSDiv(l, r);

        // TODO: 5.0 % 4 => 1
      case parser::token::PERCENT:
        if (isa<ConstantFP>(l) || isa<ConstantFP>(r))
          return b->CreateFRem(b->CreateSIToFP(l, b->getDoubleTy()), b->CreateSIToFP(r, b->getDoubleTy()));
        else
          return b->CreateSRem(l, r);
      case parser::token::LT:
      {
        if (isa<ConstantFP>(l) || isa<ConstantFP>(r))
          l = b->CreateFCmpOLT(b->CreateSIToFP(l, b->getDoubleTy()), b->CreateSIToFP(r, b->getDoubleTy()));
        else
          l = b->CreateICmpSLT(l, r);
        l = b->CreateUIToFP(l, b->getDoubleTy());
        return b->CreateFPToSI(l, b->getInt64Ty());
      }
      case parser::token::GT:
      {
        if (isa<ConstantFP>(l) || isa<ConstantFP>(r))
          l = b->CreateFCmpOGT(b->CreateSIToFP(l, b->getDoubleTy()), b->CreateSIToFP(r, b->getDoubleTy()));
        else
          l = b->CreateICmpSGT(l, r);
        l = b->CreateUIToFP(l, b->getDoubleTy());
        return b->CreateFPToSI(l, b->getInt64Ty());
      }
      case parser::token::LTE:
      {
        if (isa<ConstantFP>(l) || isa<ConstantFP>(r))
          l = b->CreateFCmpOLE(b->CreateSIToFP(l, b->getDoubleTy()), b->CreateSIToFP(r, b->getDoubleTy()));
        else
          l = b->CreateICmpSLE(l, r);
        l = b->CreateUIToFP(l, b->getDoubleTy());
        return b->CreateFPToSI(l, b->getInt64Ty());
      }
      case parser::token::GTE:
      {
        if (isa<ConstantFP>(l) || isa<ConstantFP>(r))
          l = b->CreateFCmpOGE(b->CreateSIToFP(l, b->getDoubleTy()), b->CreateSIToFP(r, b->getDoubleTy()));
        else
          l = b->CreateICmpSGE(l, r);
        l = b->CreateUIToFP(l, b->getDoubleTy());
        return b->CreateFPToSI(l, b->getInt64Ty());
      }
      case parser::token::EE:
      {
        if (isa<ConstantFP>(l) || isa<ConstantFP>(r))
          l = b->CreateFCmpOEQ(b->CreateSIToFP(l, b->getDoubleTy()), b->CreateSIToFP(r, b->getDoubleTy()));
        else
          l = b->CreateICmpEQ(l, r);
        l = b->CreateUIToFP(l, b->getDoubleTy());
        return b->CreateFPToSI(l, b->getInt64Ty());
      }
      case parser::token::NE:
      {
        if (isa<ConstantFP>(l) || isa<ConstantFP>(r))
        {
          l = b->CreateFCmpONE(b->CreateSIToFP(l, b->getDoubleTy()), b->CreateSIToFP(r, b->getDoubleTy()));
        }
        else
        {
          l = b->CreateICmpNE(l, r);
        }
        // 0.0 / 1.0
        l = b->CreateUIToFP(l, b->getDoubleTy());

        // 0.0 / 1.0 -> 0 / 1
        return b->CreateFPToSI(l, b->getInt64Ty());
      }
      default:
        break;
      }
    }

    Value *cg_call(CallAst *ast)
    {
      if (auto *F = dyn_cast<Function>(codegen(ast->name)))
      {
        std::vector<Value *> argv;
        if (F->getName().str() == "print")
        {
          argv.push_back(b->getInt64(ast->args.size() - 1));
          for (auto a : ast->args)
          {
            auto v = codegen(a);
            if (v->getType()->isDoubleTy())
            {
              auto d = reinterpret_cast<ConstantFP *>(v)->getValueAPF().convertToDouble();
              v = b->CreateGlobalStringPtr(std::to_string(d));
            }
            else if (v->getType()->isIntegerTy())
            {
              auto a = reinterpret_cast<ConstantInt *>(v);
              v = b->CreateGlobalStringPtr(std::to_string(a->getSExtValue()));
            }
            argv.push_back(v);
          }
        }
        else
        {
          for (auto a : ast->args)
            argv.push_back(codegen(a));
        }
        return b->CreateCall(F, argv);
      }
      else
      {
        auto id = ast->name->id();
        if (id == xxs::AT::VarAccess || id == xxs::AT::Function)
          throw std::exception(std::format("{} is not defined", ast->name->toString()).data());
        else
          throw std::exception(std::format("{} is not a function", ast->name->toString()).data());
      }
    }

    Value *cg_function(FuncAst *ast)
    {
      // main先加上scope
      if (ctx.scopes.empty())
      {
        ++ctx;
        declares();
      }

      auto parentBB = b->GetInsertBlock();
      SmallVector<Type *> params(ast->params.size(), b->getInt64Ty());
      auto ftype = FunctionType::get(b->getInt64Ty(), params, false);
      auto F = Function::Create(ftype, Function::ExternalLinkage, ast->name, m.get());

      // 将函数添加到当前scope，在创建新的scope
      ctx.setf(ast->name, F);
      ++ctx;

      auto BB = BasicBlock::Create(*llctx, "entry", F);
      b->SetInsertPoint(BB);

      // set arg name
      int i = 0;
      for (auto &arg : F->args())
        arg.setName(ast->params[i++]);

      // 处理函数的参数列表
      for (auto &Arg : F->args())
      {
        auto argname = Arg.getName().str();
        auto *aa = CreateEntryBlockAlloca(F, Arg.getType(), argname);
        b->CreateStore(&Arg, aa);
        ctx.set(argname, aa);
      }

      bool notRet = true;
      if (cg_stmts(ast->body)->getType()->getTypeID() == Type::TypeID::VoidTyID)
      {
        notRet = false;
      }

      // 默认返回0
      if (notRet)
        b->CreateRet(b->getInt64(0));

      verifyFunction(*F);
      b->SetInsertPoint(parentBB ? parentBB : BB);

      // 为函数添加优化器
      fmp->run(*F);

      --ctx;
      return F;
    }

    Value *cg_stmts(StmtsAst *ast)
    {
      if (ast->stmts.empty())
        return b->getInt64(0);

      Value *v = nullptr;
      for (auto s : ast->stmts)
      {
        // return 直接返回
        if (s->id() == xxs::AT::Ret)
          return cg_ret(reinterpret_cast<xxs::RetAst *>(s));

        // break和continue之后的stmt将被无视
        if (s->id() == xxs::AT::Break)
          return cg_break(reinterpret_cast<xxs::BreakAst *>(s));
        if (s->id() == xxs::AT::Continue)
          return cg_continue(reinterpret_cast<xxs::ContinueAst *>(s));

        // other
        if (ast->lastVal)
          v = codegen(s);
        else
          !v ? v = codegen(s) : codegen(s);
      }
      return v;
    }

    Value *cg_if(IfAst *ast)
    {
      if (ast->th->empty() && ast->el->empty())
        return b->getInt1(0);

      auto F = b->GetInsertBlock()->getParent();

      auto MergeBB = BasicBlock::Create(*llctx, "merge", F);
      BasicBlock *ThenBB = BasicBlock::Create(*llctx, "then");
      BasicBlock *ElseBB = BasicBlock::Create(*llctx, "else");

      auto cond = codegen(ast->cond);

      if (ast->th->empty() && !ast->el->empty())
        b->CreateCondBr(cond, MergeBB, ElseBB);
      else if (!ast->th->empty() && ast->el->empty())
        b->CreateCondBr(cond, ThenBB, MergeBB);
      else
        b->CreateCondBr(cond, ThenBB, ElseBB);

      Value *ThenV = b->getInt64(0);
      if (!ast->th->stmts.empty())
      {
        F->getBasicBlockList().push_back(ThenBB);
        b->SetInsertPoint(ThenBB);
        ThenV = cg_stmts(ast->th);
        // break stmd and continue stmt return nullptr
        // return stmt return type is VoidTyID
        // 解决多个br的BUG和ret
        if (ThenV && !ThenV->getType()->isVoidTy())
        {
          b->CreateBr(MergeBB);
        };
      }
      ThenBB = b->GetInsertBlock();

      Value *ElseV = b->getInt64(0);
      if (!ast->el->empty())
      {
        F->getBasicBlockList().push_back(ElseBB);
        b->SetInsertPoint(ElseBB);
        ElseV = cg_stmts(ast->el);
        // 做和then一样的事
        if (ElseV && !ElseV->getType()->isVoidTy())
        {
          b->CreateBr(MergeBB);
        };
      }
      ElseBB = b->GetInsertBlock();

      b->SetInsertPoint(MergeBB);
      auto PN = b->CreatePHI(ThenV->getType(), 2);
      PN->addIncoming(ThenV, ThenBB);
      PN->addIncoming(ElseV, ElseBB);
      return PN;
    }

    Value *cg_for(ForAst *ast)
    {
      auto F = b->GetInsertBlock()->getParent();
      auto parentBB = b->GetInsertBlock();

      // 初始化init表达式
      if (ast->init)
        codegen(ast->init);

      // 进入loop循环
      auto LoopBB = BasicBlock::Create(*llctx, "loop", F);
      auto LoopBodyBB = BasicBlock::Create(*llctx, "loop.body", F);
      auto LoopStepBB = BasicBlock::Create(*llctx, "loop.step", F);
      auto LoopEndBB = BasicBlock::Create(*llctx, "loop.end", F);

      breakBB = LoopEndBB;
      continueBB = LoopStepBB;

      b->CreateBr(LoopBB);
      b->SetInsertPoint(LoopBB);

      if (ast->cond)
        b->CreateCondBr(codegen(ast->cond), LoopBodyBB, LoopEndBB);
      else
        b->CreateBr(LoopBodyBB);

      b->SetInsertPoint(LoopBodyBB);
      codegen(ast->body);
      b->CreateBr(LoopStepBB);

      b->SetInsertPoint(LoopStepBB);
      if (ast->step)
        codegen(ast->step);
      b->CreateBr(LoopBB);

      b->SetInsertPoint(LoopEndBB);
      return b->getInt1(0);
    }

    Value *cg_varAssign(VarAssignAst *ast)
    {
      switch (ast->op)
      {
      case parser::token::EQ:
      {
        auto Alloca = ctx.get(ast->name);
        auto val = codegen(ast->right);
        if (Alloca)
          b->CreateStore(val, Alloca);
        else
        {
          auto F = b->GetInsertBlock()->getParent();
          auto Alloca = CreateEntryBlockAlloca(F, val->getType(), ast->name);
          b->CreateStore(val, Alloca);
          ctx.set(ast->name, Alloca);
        }
        return val;
      }
      }
    }

    nullptr_t cg_break(BreakAst *ast)
    {
      if (!breakBB)
        throw std::exception("Illegal break statement");

      b->CreateBr(breakBB);
      breakBB = nullptr;
      return nullptr;
    }

    nullptr_t cg_continue(ContinueAst *ast)
    {
      if (!continueBB)
        throw std::exception("Illegal continue statement");
      b->CreateBr(continueBB);
      continueBB = nullptr;
      return nullptr;
    }

    Value *cg_ret(RetAst *ast)
    {
      auto r = b->CreateRet(ast->val ? codegen(ast->val) : b->getInt64(0));
      return r;
    }

    Value *cg_list(ListAst *ast)
    {
      // TODO::
      return nullptr;
    }

    AllocaInst *CreateEntryBlockAlloca(Function *fun, Type *type, std::string_view VarName)
    {
      // 创建了一个指向入口块的第一条指令 (.begin()) 的 IRBuilder 对象
      IRBuilder<> TmpB(&fun->getEntryBlock(), fun->getEntryBlock().begin());
      // 然后它创建一个具有预期名称的 alloca 并返回它
      return TmpB.CreateAlloca(type, nullptr, VarName.data());
    }
  };

}
