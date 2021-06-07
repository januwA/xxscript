#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace xxs
{

#define PAST xxs::Ast *

  enum class AT
  {
    Int,
    Float,
    VarAccess,
    Binary,
    Call,
    Function,
    Block,
    VarAssign,
    Ret,
    If,
    For,
    While,
  };
  struct Ast
  {
    virtual AT id() = 0;
  };

  struct IntAst : public Ast
  {
    int num{0};
    IntAst(int num) : num(num) {}
    AT id() { return AT::Int; }
  };

  struct FloatAst : public Ast
  {
    float num{0};
    FloatAst(float num) : num(num) {}
    AT id() { return AT::Float; }
  };

  struct VarAccessAst : public Ast
  {
    std::string name;
    VarAccessAst(std::string_view name) : name(name) {}
    AT id() { return AT::VarAccess; }
  };

  struct VarAssignAst : public Ast
  {
    std::string name;
    int op;
    PAST right;
    VarAssignAst(std::string name, int op, PAST right) : op(op), name(name), right(right) {}
    ~VarAssignAst() { delete right; }
    AT id() override { return AT::VarAssign; }
  };

  struct BinaryAst : public Ast
  {
    int op;
    PAST left;
    PAST right;
    BinaryAst(int op, PAST left, PAST right) : op(op), left(left), right(right) {}
    ~BinaryAst()
    {
      delete left;
      delete right;
    }
    AT id() override { return AT::Binary; }
  };

  struct CallAst : public Ast
  {
    PAST name;
    std::vector<PAST> args;
    CallAst(PAST name) : name(name), args(0) {}
    CallAst(PAST name, std::vector<PAST> args) : name(name), args(args) {}
    ~CallAst()
    {
      delete name;
      for (auto a : args)
        delete a;
    }
    AT id() { return AT::Call; }
  };

  struct FunctionAst : public Ast
  {
    std::string name;
    std::vector<std::string> params;
    PAST body;
    FunctionAst(std::string_view name, std::vector<std::string> params, PAST body) : name(name.data()), params(params), body(body) {}
    FunctionAst(std::vector<std::string> params, PAST body) : name(""), params(params), body(body) {}
    ~FunctionAst() { delete body; }
    AT id() { return AT::Function; }
  };

  struct BlockAst : public Ast
  {
    std::vector<PAST> blocks;
    BlockAst() : blocks(0) {}
    BlockAst(std::vector<PAST> blocks) : blocks(blocks) {}
    ~BlockAst()
    {
      for (auto a : blocks)
        delete a;
    }

    AT id() { return AT::Block; }
    void push(PAST ast)
    {
      blocks.push_back(ast);
    }
  };

  struct RetAst : public Ast
  {
    PAST val;
    RetAst(PAST val) : val(val) {}
    RetAst() : val(nullptr) {}
    ~RetAst() { delete val; }
    AT id() { return AT::Ret; }
  };

}
