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
    Str,
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
    Break,
    Continue,
    Bool,
  };
  struct Ast
  {
    virtual AT id() = 0;
    virtual std::string toString() = 0;
  };

  typedef xxs::Ast *ast_ptr;

  struct StmtsAst : public Ast
  {
    // stmts表达式，默认返回最后一个ast_ptr的value
    // 设置为false将返回第一个ast_ptr的value
    // 为空返回0
    bool lastVal{true};
    std::vector<ast_ptr> stmts;

    StmtsAst() : stmts(0) {}
    StmtsAst(std::vector<ast_ptr> blocks, bool lastVal = true) : stmts(blocks), lastVal(lastVal) {}
    ~StmtsAst()
    {
      for (auto a : stmts)
        delete a;
    }

    bool empty() const { return stmts.empty(); }

    AT id() { return AT::Stmts; }
    std::string toString()
    {
      return "{  }";
    }

    void push(ast_ptr ast)
    {
      stmts.push_back(ast);
    }
  };
  typedef xxs::StmtsAst *stmts_ptr;

  struct IntAst : public Ast
  {
    int64_t num{0};
    IntAst(int num) : num(num) {}
    AT id() { return AT::Int; }
    std::string toString() { return std::to_string(num); };
  };

  struct FloatAst : public Ast
  {
    double num{0};
    FloatAst(double num) : num(num) {}
    AT id() { return AT::Float; }
    std::string toString() { return std::to_string(num); };
  };

  struct StrAst : public Ast
  {
    std::string str;
    StrAst(std::string_view str) : str(str) {}
    AT id() { return AT::Str; }
    std::string toString() { return str; };
  };

  struct VarAccessAst : public Ast
  {
    std::string name;
    VarAccessAst(std::string_view name) : name(name) {}
    AT id() { return AT::VarAccess; }
    std::string toString() { return name; };
  };

  struct VarAssignAst : public Ast
  {
    std::string name;
    int op;
    ast_ptr right;
    VarAssignAst(std::string name, int op, ast_ptr right) : op(op), name(name), right(right) {}
    ~VarAssignAst() { delete right; }
    AT id() override { return AT::VarAssign; }
    std::string toString()
    {
      return std::format("{} = {}", name, right->toString());
    };
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
    std::string toString()
    {
      return std::format("{} op {}", left->toString(), right->toString());
    };
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
    std::string toString()
    {
      return std::format("{}(...)", name->toString());
    };
  };

  struct FuncAst : public Ast
  {
    std::string name;
    params_t params;
    stmts_ptr body;

    FuncAst(std::string_view name, params_t params, stmts_ptr body) : name(name.data()), params(params), body(body) {}
    ~FuncAst() { delete body; }

    AT id() { return AT::Function; }
    std::string toString()
    {
      return std::format("function {}(...){ }", name);
    };
  };

  struct RetAst : public Ast
  {
    ast_ptr val;

    RetAst(ast_ptr val) : val(val) {}
    RetAst() : val(nullptr) {}
    ~RetAst() { delete val; }

    AT id() { return AT::Ret; }
    std::string toString()
    {
      return std::format("return {}", val ? "" : val->toString());
    };
  };

  struct BreakAst : public Ast
  {
    BreakAst() {}
    AT id() { return AT::Break; }
    std::string toString()
    {
      return std::format("break");
    };
  };

  struct ContinueAst : public Ast
  {
    ContinueAst() {}
    AT id() { return AT::Continue; }
    std::string toString()
    {
      return std::format("break");
    };
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
    std::string toString()
    {
      return std::format("if ({}) {}", cond->toString());
    };
  };

  struct ForAst : public Ast
  {
    ast_ptr init{nullptr};
    ast_ptr cond{nullptr};
    ast_ptr step{nullptr};
    stmts_ptr body;

    ForAst(ast_ptr init, ast_ptr cond, ast_ptr step, stmts_ptr body)
        : cond(cond), init(init), step(step), body(body) {}
    ~ForAst()
    {
      if (init)
        delete init;
      if (cond)
        delete cond;
      if (step)
        delete step;
      delete body;
    }
    AT id() { return AT::For; }
    std::string toString()
    {
      return std::format("for (;;) { }");
    };
  };

}
