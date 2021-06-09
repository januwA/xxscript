// A Bison parser, made by GNU Bison 3.7.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.


// Take the name prefix into account.
#define yylex   xxslex



#include "parser.h"


// Unqualified %code blocks.
#line 29 "parser.y"

  #include <iostream>
  #include "ast.hpp"

  extern xxs::parser::symbol_type yylex();

#line 55 "parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if XXSDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !XXSDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !XXSDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace xxs {
#line 147 "parser.cpp"

  /// Build a parser object.
  parser::parser (xxs::FuncAst *& _main_yyarg)
#if XXSDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      _main (_main_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_exprs: // exprs
        value.YY_MOVE_OR_COPY< asts_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT: // "float"
        value.YY_MOVE_OR_COPY< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // "int"
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_idents: // idents
        value.YY_MOVE_OR_COPY< params_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENT: // "identifier"
      case symbol_kind::S_func_begin: // func_begin
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_block_1: // block_1
      case symbol_kind::S_block_2: // block_2
      case symbol_kind::S_else_1: // else_1
        value.YY_MOVE_OR_COPY< xxs::StmtsAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_for_begin: // for_begin
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_for_step: // for_step
      case symbol_kind::S_expr_1: // expr_1
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_primary: // primary
        value.YY_MOVE_OR_COPY< xxs::ast_ptr > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_exprs: // exprs
        value.move< asts_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT: // "float"
        value.move< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // "int"
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_idents: // idents
        value.move< params_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENT: // "identifier"
      case symbol_kind::S_func_begin: // func_begin
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_block_1: // block_1
      case symbol_kind::S_block_2: // block_2
      case symbol_kind::S_else_1: // else_1
        value.move< xxs::StmtsAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_for_begin: // for_begin
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_for_step: // for_step
      case symbol_kind::S_expr_1: // expr_1
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_primary: // primary
        value.move< xxs::ast_ptr > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_exprs: // exprs
        value.copy< asts_t > (that.value);
        break;

      case symbol_kind::S_FLOAT: // "float"
        value.copy< float > (that.value);
        break;

      case symbol_kind::S_INT: // "int"
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_idents: // idents
        value.copy< params_t > (that.value);
        break;

      case symbol_kind::S_IDENT: // "identifier"
      case symbol_kind::S_func_begin: // func_begin
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_block_1: // block_1
      case symbol_kind::S_block_2: // block_2
      case symbol_kind::S_else_1: // else_1
        value.copy< xxs::StmtsAst* > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_for_begin: // for_begin
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_for_step: // for_step
      case symbol_kind::S_expr_1: // expr_1
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_primary: // primary
        value.copy< xxs::ast_ptr > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_exprs: // exprs
        value.move< asts_t > (that.value);
        break;

      case symbol_kind::S_FLOAT: // "float"
        value.move< float > (that.value);
        break;

      case symbol_kind::S_INT: // "int"
        value.move< int > (that.value);
        break;

      case symbol_kind::S_idents: // idents
        value.move< params_t > (that.value);
        break;

      case symbol_kind::S_IDENT: // "identifier"
      case symbol_kind::S_func_begin: // func_begin
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_block_1: // block_1
      case symbol_kind::S_block_2: // block_2
      case symbol_kind::S_else_1: // else_1
        value.move< xxs::StmtsAst* > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_for_begin: // for_begin
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_for_step: // for_step
      case symbol_kind::S_expr_1: // expr_1
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_primary: // primary
        value.move< xxs::ast_ptr > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if XXSDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YYUSE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if XXSDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // XXSDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_exprs: // exprs
        yylhs.value.emplace< asts_t > ();
        break;

      case symbol_kind::S_FLOAT: // "float"
        yylhs.value.emplace< float > ();
        break;

      case symbol_kind::S_INT: // "int"
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_idents: // idents
        yylhs.value.emplace< params_t > ();
        break;

      case symbol_kind::S_IDENT: // "identifier"
      case symbol_kind::S_func_begin: // func_begin
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_block_1: // block_1
      case symbol_kind::S_block_2: // block_2
      case symbol_kind::S_else_1: // else_1
        yylhs.value.emplace< xxs::StmtsAst* > ();
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_for_begin: // for_begin
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_for_step: // for_step
      case symbol_kind::S_expr_1: // expr_1
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_primary: // primary
        yylhs.value.emplace< xxs::ast_ptr > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // main: stmts $end
#line 63 "parser.y"
                                                                { _main = new FuncAst("main", params_t(), yystack_[1].value.as < xxs::StmtsAst* > ());    }
#line 731 "parser.cpp"
    break;

  case 3: // main: $end
#line 64 "parser.y"
                                                                { _main = nullptr;                                      }
#line 737 "parser.cpp"
    break;

  case 4: // stmts: stmt
#line 67 "parser.y"
                                                                { yylhs.value.as < xxs::StmtsAst* > () = new StmtsAst({yystack_[0].value.as < xxs::ast_ptr > ()});                              }
#line 743 "parser.cpp"
    break;

  case 5: // stmts: stmts stmt
#line 68 "parser.y"
                                                                { yylhs.value.as < xxs::StmtsAst* > () = yystack_[1].value.as < xxs::StmtsAst* > (); yylhs.value.as < xxs::StmtsAst* > ()->push(yystack_[0].value.as < xxs::ast_ptr > ());                                }
#line 749 "parser.cpp"
    break;

  case 6: // stmt: expr_1
#line 72 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > ()=yystack_[0].value.as < xxs::ast_ptr > ();                                                }
#line 755 "parser.cpp"
    break;

  case 7: // stmt: expr_1 ";"
#line 73 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > ()=yystack_[1].value.as < xxs::ast_ptr > ();                                                }
#line 761 "parser.cpp"
    break;

  case 8: // stmt: "return" expr_1 ";"
#line 74 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = new RetAst(yystack_[1].value.as < xxs::ast_ptr > ());                                  }
#line 767 "parser.cpp"
    break;

  case 9: // stmt: "return" ";"
#line 75 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = new RetAst();                                    }
#line 773 "parser.cpp"
    break;

  case 10: // stmt: "if" "(" expr_1 ")" block_2 else_1
#line 76 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = new IfAst(yystack_[3].value.as < xxs::ast_ptr > (), yystack_[1].value.as < xxs::StmtsAst* > (), yystack_[0].value.as < xxs::StmtsAst* > ());                }
#line 779 "parser.cpp"
    break;

  case 11: // stmt: for_begin for_cond ";" for_step ")" block_2
#line 77 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = new ForAst(yystack_[5].value.as < xxs::ast_ptr > (), yystack_[4].value.as < xxs::ast_ptr > (), yystack_[2].value.as < xxs::ast_ptr > (), yystack_[0].value.as < xxs::StmtsAst* > ());                }
#line 785 "parser.cpp"
    break;

  case 12: // stmt: "while" "(" expr_1 ")" block_2
#line 78 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = new ForAst(nullptr, yystack_[2].value.as < xxs::ast_ptr > (), nullptr, yystack_[0].value.as < xxs::StmtsAst* > ());   }
#line 791 "parser.cpp"
    break;

  case 13: // stmt: "continue" ";"
#line 79 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = new ContinueAst();                               }
#line 797 "parser.cpp"
    break;

  case 14: // stmt: "break" ";"
#line 80 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = new BreakAst();                                  }
#line 803 "parser.cpp"
    break;

  case 15: // block_1: "{" stmts "}"
#line 83 "parser.y"
                                                                { yylhs.value.as < xxs::StmtsAst* > () = yystack_[1].value.as < xxs::StmtsAst* > ();                                          }
#line 809 "parser.cpp"
    break;

  case 16: // block_1: "{" "}"
#line 84 "parser.y"
                                                                { yylhs.value.as < xxs::StmtsAst* > () = new StmtsAst();                                  }
#line 815 "parser.cpp"
    break;

  case 17: // block_2: block_1
#line 87 "parser.y"
                                                                { yylhs.value.as < xxs::StmtsAst* > () = yystack_[0].value.as < xxs::StmtsAst* > ();                                              }
#line 821 "parser.cpp"
    break;

  case 18: // block_2: stmt
#line 88 "parser.y"
                                                                { yylhs.value.as < xxs::StmtsAst* > () = new StmtsAst({ yystack_[0].value.as < xxs::ast_ptr > () });                            }
#line 827 "parser.cpp"
    break;

  case 19: // for_begin: "for" "(" expr_1 ";"
#line 92 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = yystack_[1].value.as < xxs::ast_ptr > ();                                         }
#line 833 "parser.cpp"
    break;

  case 20: // for_begin: "for" "(" ";"
#line 93 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = nullptr;                                         }
#line 839 "parser.cpp"
    break;

  case 21: // for_cond: expr_1
#line 96 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = yystack_[0].value.as < xxs::ast_ptr > ();                                              }
#line 845 "parser.cpp"
    break;

  case 22: // for_cond: %empty
#line 97 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = nullptr;                                         }
#line 851 "parser.cpp"
    break;

  case 23: // for_step: expr_1
#line 100 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = yystack_[0].value.as < xxs::ast_ptr > ();                                              }
#line 857 "parser.cpp"
    break;

  case 24: // for_step: %empty
#line 101 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = nullptr;                                         }
#line 863 "parser.cpp"
    break;

  case 25: // else_1: %empty
#line 104 "parser.y"
                                                                { yylhs.value.as < xxs::StmtsAst* > () = new StmtsAst();                                  }
#line 869 "parser.cpp"
    break;

  case 26: // else_1: "else" block_2
#line 105 "parser.y"
                                                                { yylhs.value.as < xxs::StmtsAst* > () = yystack_[0].value.as < xxs::StmtsAst* > ();                                              }
#line 875 "parser.cpp"
    break;

  case 27: // expr_1: "identifier" "=" expr_1
#line 108 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = new VarAssignAst(yystack_[2].value.as < std::string > (), token::EQ, yystack_[0].value.as < xxs::ast_ptr > ());             }
#line 881 "parser.cpp"
    break;

  case 28: // expr_1: expr
#line 109 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = yystack_[0].value.as < xxs::ast_ptr > ();                                              }
#line 887 "parser.cpp"
    break;

  case 29: // expr_1: func_begin "(" idents ")" block_1
#line 110 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = new FuncAst(yystack_[4].value.as < std::string > (), std::move(yystack_[2].value.as < params_t > ()), yystack_[0].value.as < xxs::StmtsAst* > ());   }
#line 893 "parser.cpp"
    break;

  case 30: // func_begin: "function" "identifier"
#line 113 "parser.y"
                                                                { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > ();                                              }
#line 899 "parser.cpp"
    break;

  case 31: // func_begin: "function"
#line 114 "parser.y"
                                                                { yylhs.value.as < std::string > () = "";                                              }
#line 905 "parser.cpp"
    break;

  case 32: // expr: primary
#line 117 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = yystack_[0].value.as < xxs::ast_ptr > ();                                              }
#line 911 "parser.cpp"
    break;

  case 33: // expr: "(" expr_1 ")"
#line 118 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = yystack_[1].value.as < xxs::ast_ptr > ();                                              }
#line 917 "parser.cpp"
    break;

  case 34: // expr: expr "(" exprs ")"
#line 119 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = new CallAst(yystack_[3].value.as < xxs::ast_ptr > (), std::move(yystack_[1].value.as < asts_t > ()));                  }
#line 923 "parser.cpp"
    break;

  case 35: // expr: expr "+" expr
#line 120 "parser.y"
                                                                { BINARY(PLUS);                                         }
#line 929 "parser.cpp"
    break;

  case 36: // expr: expr "-" expr
#line 121 "parser.y"
                                                                { BINARY(MINUS);                                        }
#line 935 "parser.cpp"
    break;

  case 37: // expr: expr "*" expr
#line 122 "parser.y"
                                                                { BINARY(MUL);                                          }
#line 941 "parser.cpp"
    break;

  case 38: // expr: expr "/" expr
#line 123 "parser.y"
                                                                { BINARY(DIV);                                          }
#line 947 "parser.cpp"
    break;

  case 39: // expr: expr ">" expr
#line 124 "parser.y"
                                                                { BINARY(GT);                                           }
#line 953 "parser.cpp"
    break;

  case 40: // expr: expr "<" expr
#line 125 "parser.y"
                                                                { BINARY(LT);                                           }
#line 959 "parser.cpp"
    break;

  case 41: // expr: expr ">=" expr
#line 126 "parser.y"
                                                                { BINARY(GTE);                                          }
#line 965 "parser.cpp"
    break;

  case 42: // expr: expr "<=" expr
#line 127 "parser.y"
                                                                { BINARY(LTE);                                          }
#line 971 "parser.cpp"
    break;

  case 43: // expr: expr "==" expr
#line 128 "parser.y"
                                                                { BINARY(EE);                                           }
#line 977 "parser.cpp"
    break;

  case 44: // expr: expr "!=" expr
#line 129 "parser.y"
                                                                { BINARY(NE);                                           }
#line 983 "parser.cpp"
    break;

  case 45: // expr: "identifier" "++"
#line 130 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = new StmtsAst{{ new VarAccessAst(yystack_[1].value.as < std::string > ()), IPPMM(1, PLUS), }, false}; }
#line 989 "parser.cpp"
    break;

  case 46: // expr: "identifier" "--"
#line 131 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = new StmtsAst{{ new VarAccessAst(yystack_[1].value.as < std::string > ()), IPPMM(1, MINUS) }, false}; }
#line 995 "parser.cpp"
    break;

  case 47: // expr: "++" "identifier"
#line 132 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = IPPMM(0, PLUS);                                  }
#line 1001 "parser.cpp"
    break;

  case 48: // expr: "--" "identifier"
#line 133 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = IPPMM(0, MINUS);                                 }
#line 1007 "parser.cpp"
    break;

  case 49: // primary: "int"
#line 136 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = new IntAst(yystack_[0].value.as < int > ());                                  }
#line 1013 "parser.cpp"
    break;

  case 50: // primary: "nil"
#line 137 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = new IntAst(NULL);                                }
#line 1019 "parser.cpp"
    break;

  case 51: // primary: "float"
#line 138 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = new FloatAst(yystack_[0].value.as < float > ());                                }
#line 1025 "parser.cpp"
    break;

  case 52: // primary: "identifier"
#line 139 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = new VarAccessAst(yystack_[0].value.as < std::string > ());                            }
#line 1031 "parser.cpp"
    break;

  case 53: // idents: %empty
#line 142 "parser.y"
                                                                 { yylhs.value.as < params_t > () = params_t();                                     }
#line 1037 "parser.cpp"
    break;

  case 54: // idents: "identifier"
#line 143 "parser.y"
                                                                 { yylhs.value.as < params_t > () = params_t{yystack_[0].value.as < std::string > ()};                                   }
#line 1043 "parser.cpp"
    break;

  case 55: // idents: idents "," "identifier"
#line 144 "parser.y"
                                                                 { yylhs.value.as < params_t > () = std::move(yystack_[2].value.as < params_t > ()); yylhs.value.as < params_t > ().push_back(yystack_[0].value.as < std::string > ());                }
#line 1049 "parser.cpp"
    break;

  case 56: // exprs: %empty
#line 147 "parser.y"
                                                                 { yylhs.value.as < asts_t > () = asts_t();                                       }
#line 1055 "parser.cpp"
    break;

  case 57: // exprs: expr_1
#line 148 "parser.y"
                                                                 { yylhs.value.as < asts_t > () = asts_t{yystack_[0].value.as < xxs::ast_ptr > ()};                                     }
#line 1061 "parser.cpp"
    break;

  case 58: // exprs: exprs "," expr_1
#line 149 "parser.y"
                                                                 { yylhs.value.as < asts_t > () = std::move(yystack_[2].value.as < asts_t > ()); yylhs.value.as < asts_t > ().push_back(yystack_[0].value.as < xxs::ast_ptr > ());                }
#line 1067 "parser.cpp"
    break;


#line 1071 "parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

#if XXSDEBUG || 0
  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if XXSDEBUG || 0





  const signed char parser::yypact_ninf_ = -78;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
      58,   -78,   -13,   -15,    -2,     4,   -22,     1,   -78,    11,
     -78,   -78,   -14,    20,    24,   184,    40,    92,   -78,   184,
      17,    13,   203,   -78,   -78,   184,    32,   184,   -78,   -78,
     -78,    18,   -78,   -78,   184,   -78,   -78,    25,   -78,   -78,
     -78,    21,   -78,   -78,    41,   195,   195,   195,   195,   195,
     195,   195,   195,   195,   195,   184,    28,   -78,    27,    44,
     -78,   -78,   -78,   184,   -78,   -26,     9,    19,    19,    46,
      46,    66,    66,   217,    66,    66,   217,   -78,   -18,   172,
     -78,   172,    47,   -78,    45,    65,   -78,   184,   114,   -78,
     -78,    79,   -78,   172,   -78,   -78,   -78,   -78,   143,   172,
     -78,   -78,   -78,   -78
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     3,    31,     0,     0,     0,     0,     0,    50,     0,
      49,    51,    52,     0,     0,     0,     0,     0,     4,    22,
       6,     0,    28,    32,    30,     0,     0,     0,    13,    14,
       9,     0,    45,    46,     0,    47,    48,     0,     1,     2,
       5,     0,    21,     7,    53,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    56,     0,    20,     0,     0,
       8,    27,    33,    24,    54,     0,    52,    35,    36,    37,
      38,    40,    39,    43,    42,    41,    44,    57,     0,     0,
      19,     0,     0,    23,     0,     0,    34,     0,     0,    18,
      17,    25,    12,     0,    29,    55,    58,    16,     0,     0,
      10,    11,    15,    26
  };

  const short
  parser::yypgoto_[] =
  {
     -78,   -78,    -1,     0,     5,   -77,   -78,   -78,   -78,   -78,
      -7,   -78,   201,   -78,   -78,   -78
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,    16,    17,    89,    90,    91,    19,    41,    82,   100,
      20,    21,    22,    23,    65,    78
  };

  const signed char
  parser::yytable_[] =
  {
      18,    24,    31,    84,    92,    32,    33,    85,    37,    34,
      28,    86,    42,    25,     2,    87,   101,    40,    56,    58,
      59,     8,   103,    10,    11,    12,    26,    61,    32,    33,
      13,    14,    27,    29,    35,     2,    47,    48,    36,    15,
      38,    44,     8,    30,    10,    11,    12,    55,    77,    43,
      60,    13,    14,    63,    62,    64,    83,    79,     1,    80,
      15,     2,     3,     4,    57,     5,     6,     7,     8,     9,
      10,    11,    12,    81,    55,    88,    93,    13,    14,    95,
      96,    45,    46,    47,    48,    99,    15,    98,    18,    94,
       0,     0,    39,     0,    55,     2,     3,     4,    40,     5,
       6,     7,     8,     9,    10,    11,    12,     0,     0,     0,
       0,    13,    14,     0,     0,     0,     0,     2,     3,     4,
      15,     5,     6,     7,     8,     9,    10,    11,    12,     0,
       0,     0,     0,    13,    14,     0,     0,     0,     0,     0,
       0,     0,    15,     0,     0,    97,     2,     3,     4,     0,
       5,     6,     7,     8,     9,    10,    11,    12,     0,     0,
       0,     0,    13,    14,     0,     0,     0,     0,     0,     0,
       0,    15,     0,     0,   102,     2,     3,     4,     0,     5,
       6,     7,     8,     9,    10,    11,    12,     2,     0,     0,
       0,    13,    14,     0,     8,     0,    10,    11,    12,     0,
      15,     0,    88,    13,    14,     8,     0,    10,    11,    66,
       0,     0,    15,     0,    13,    14,     0,     0,    45,    46,
      47,    48,     0,    15,    49,    50,     0,    51,    52,    53,
      54,    55,    45,    46,    47,    48,     0,     0,    49,    50,
       0,     0,    52,    53,     0,    55,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76
  };

  const signed char
  parser::yycheck_[] =
  {
       0,    14,     9,    29,    81,    19,    20,    33,    15,    23,
      32,    29,    19,    28,     3,    33,    93,    17,    25,    26,
      27,    10,    99,    12,    13,    14,    28,    34,    19,    20,
      19,    20,    28,    32,    14,     3,    17,    18,    14,    28,
       0,    28,    10,    32,    12,    13,    14,    28,    55,    32,
      32,    19,    20,    32,    29,    14,    63,    29,     0,    32,
      28,     3,     4,     5,    32,     7,     8,     9,    10,    11,
      12,    13,    14,    29,    28,    30,    29,    19,    20,    14,
      87,    15,    16,    17,    18,     6,    28,    88,    88,    84,
      -1,    -1,     0,    -1,    28,     3,     4,     5,    98,     7,
       8,     9,    10,    11,    12,    13,    14,    -1,    -1,    -1,
      -1,    19,    20,    -1,    -1,    -1,    -1,     3,     4,     5,
      28,     7,     8,     9,    10,    11,    12,    13,    14,    -1,
      -1,    -1,    -1,    19,    20,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    -1,    31,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    -1,    -1,
      -1,    -1,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    -1,    31,     3,     4,     5,    -1,     7,
       8,     9,    10,    11,    12,    13,    14,     3,    -1,    -1,
      -1,    19,    20,    -1,    10,    -1,    12,    13,    14,    -1,
      28,    -1,    30,    19,    20,    10,    -1,    12,    13,    14,
      -1,    -1,    28,    -1,    19,    20,    -1,    -1,    15,    16,
      17,    18,    -1,    28,    21,    22,    -1,    24,    25,    26,
      27,    28,    15,    16,    17,    18,    -1,    -1,    21,    22,
      -1,    -1,    25,    26,    -1,    28,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54
  };

  const signed char
  parser::yystos_[] =
  {
       0,     0,     3,     4,     5,     7,     8,     9,    10,    11,
      12,    13,    14,    19,    20,    28,    36,    37,    38,    41,
      45,    46,    47,    48,    14,    28,    28,    28,    32,    32,
      32,    45,    19,    20,    23,    14,    14,    45,     0,     0,
      38,    42,    45,    32,    28,    15,    16,    17,    18,    21,
      22,    24,    25,    26,    27,    28,    45,    32,    45,    45,
      32,    45,    29,    32,    14,    49,    14,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    45,    50,    29,
      32,    29,    43,    45,    29,    33,    29,    33,    30,    38,
      39,    40,    40,    29,    39,    14,    45,    31,    37,     6,
      44,    40,    31,    40
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    35,    36,    36,    37,    37,    38,    38,    38,    38,
      38,    38,    38,    38,    38,    39,    39,    40,    40,    41,
      41,    42,    42,    43,    43,    44,    44,    45,    45,    45,
      46,    46,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    48,
      48,    48,    48,    49,    49,    49,    50,    50,    50
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     1,     1,     2,     1,     2,     3,     2,
       6,     6,     5,     2,     2,     3,     2,     1,     1,     4,
       3,     1,     0,     1,     0,     0,     2,     3,     1,     5,
       2,     1,     1,     3,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     2,     1,
       1,     1,     1,     0,     1,     3,     0,     1,     3
  };


#if XXSDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"function\"",
  "\"if\"", "\"for\"", "\"else\"", "\"while\"", "\"continue\"",
  "\"break\"", "\"nil\"", "\"return\"", "\"int\"", "\"float\"",
  "\"identifier\"", "\"+\"", "\"-\"", "\"*\"", "\"/\"", "\"++\"", "\"--\"",
  "\"<\"", "\">\"", "\"=\"", "\"==\"", "\"<=\"", "\">=\"", "\"!=\"",
  "\"(\"", "\")\"", "\"{\"", "\"}\"", "\";\"", "\",\"", "\">>\"",
  "$accept", "main", "stmts", "stmt", "block_1", "block_2", "for_begin",
  "for_cond", "for_step", "else_1", "expr_1", "func_begin", "expr",
  "primary", "idents", "exprs", YY_NULLPTR
  };
#endif


#if XXSDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,    63,    63,    64,    67,    68,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    83,    84,    87,    88,    92,
      93,    96,    97,   100,   101,   104,   105,   108,   109,   110,
     113,   114,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   136,
     137,   138,   139,   142,   143,   144,   147,   148,   149
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // XXSDEBUG


} // xxs
#line 1471 "parser.cpp"

#line 152 "parser.y"


#undef BINARY
#undef IPPMM

void xxs::parser::error(const location_type& loc, const std::string& msg)
{
  throw xxs::syntax_error(loc);
}
