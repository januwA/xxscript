#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace xxs
{
  typedef std::vector<std::string> params_t;

  enum class AT
  {
    Int,
    Float,
    VarAccess,
    Binary,
    Call,
    Function,
    Stmts,
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

  typedef xxs::Ast *ast_ptr;

  struct StmtsAst : public Ast
  {
    std::vector<ast_ptr> stmts;

    StmtsAst() : stmts(0) {}
    StmtsAst(std::vector<ast_ptr> blocks) : stmts(blocks) {}
    ~StmtsAst()
    {
      for (auto a : stmts)
        delete a;
    }

    AT id() { return AT::Stmts; }
    void push(ast_ptr ast)
    {
      stmts.push_back(ast);
    }
  };
  typedef xxs::StmtsAst *stmts_ptr;

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
    ast_ptr right;
    VarAssignAst(std::string name, int op, ast_ptr right) : op(op), name(name), right(right) {}
    ~VarAssignAst() { delete right; }
    AT id() override { return AT::VarAssign; }
  };

  struct BinaryAst : public Ast
  {
    int op;
    ast_ptr left;
    ast_ptr right;
    BinaryAst(int op, ast_ptr left, ast_ptr right) : op(op), left(left), right(right) {}
    ~BinaryAst()
    {
      delete left;
      delete right;
    }
    AT id() override { return AT::Binary; }
  };

  struct CallAst : public Ast
  {
    ast_ptr name;
    std::vector<ast_ptr> args;
    CallAst(ast_ptr name) : name(name), args(0) {}
    CallAst(ast_ptr name, std::vector<ast_ptr> args) : name(name), args(args) {}
    ~CallAst()
    {
      delete name;
      for (auto a : args)
        delete a;
    }
    AT id() { return AT::Call; }
  };

  struct FuncAst : public Ast
  {
    std::string name;
    params_t params;
    stmts_ptr body;

    FuncAst(std::string_view name, params_t params, stmts_ptr body) : name(name.data()), params(params), body(body) {}
    ~FuncAst() { delete body; }

    AT id() { return AT::Function; }
  };

  struct RetAst : public Ast
  {
    ast_ptr val;
    RetAst(ast_ptr val) : val(val) {}
    RetAst() : val(nullptr) {}
    ~RetAst() { delete val; }
    AT id() { return AT::Ret; }
  };

  struct IfAst : public Ast
  {
    ast_ptr cond;
    stmts_ptr th;
    stmts_ptr el;

    IfAst(ast_ptr cond, stmts_ptr th, stmts_ptr el) : cond(cond), th(th), el(el) {}
    ~IfAst()
    {
      delete cond;
      delete th;
      delete el;
    }
    AT id() { return AT::If; }
  };

  struct ForAst : public Ast
  {
    ast_ptr   init;
    ast_ptr   cond;
    ast_ptr   step;
    stmts_ptr body;

    ForAst(ast_ptr init, ast_ptr cond, ast_ptr step, stmts_ptr body)
        : cond(cond), init(init), step(step), body(body) {}
    ~ForAst()
    {
      delete init;
      delete cond;
      delete step;
      delete body;
    }
    AT id() { return AT::For; }
  };

}
