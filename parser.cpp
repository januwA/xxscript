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

  #include <iostream>
  #include "ast.hpp"

  extern xxs::parser::symbol_type yylex();



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
                                                                                                                                                                      { _main = new FuncAst("__main", params_t(), yystack_[1].value.as < xxs::StmtsAst* > ());  }
    break;

  case 3: // stmts: stmt
                                                                                                                                                                                      { yylhs.value.as < xxs::StmtsAst* > () = new StmtsAst({yystack_[0].value.as < xxs::ast_ptr > ()}); 							          }
    break;

  case 4: // stmts: stmts stmt
                                                                                                                                                                                      { yylhs.value.as < xxs::StmtsAst* > () = yystack_[1].value.as < xxs::StmtsAst* > (); yylhs.value.as < xxs::StmtsAst* > ()->push(yystack_[0].value.as < xxs::ast_ptr > ()); 													}
    break;

  case 5: // stmt: expr_1
                                                                                                                                                                          { yylhs.value.as < xxs::ast_ptr > () = yystack_[0].value.as < xxs::ast_ptr > (); 																				}
    break;

  case 6: // stmt: expr_1 ";"
                                                            { yylhs.value.as < xxs::ast_ptr > () = yystack_[1].value.as < xxs::ast_ptr > (); 																				}
    break;

  case 7: // stmt: "return" expr_1 ";"
                                                                                                                                              { yylhs.value.as < xxs::ast_ptr > () = new RetAst(yystack_[1].value.as < xxs::ast_ptr > ()); 														}
    break;

  case 8: // stmt: "return" ";"
                                                                                                                                                                    { yylhs.value.as < xxs::ast_ptr > () = new RetAst(); 															}
    break;

  case 9: // stmt: "if" "(" expr_1 ")" block_2 else_1
                                                                                                                  { yylhs.value.as < xxs::ast_ptr > () = new IfAst(yystack_[3].value.as < xxs::ast_ptr > (), yystack_[1].value.as < xxs::StmtsAst* > (), yystack_[0].value.as < xxs::StmtsAst* > ()); 				  }
    break;

  case 10: // stmt: for_begin for_cond ";" for_step ")" block_2
                                                                        { yylhs.value.as < xxs::ast_ptr > () = new ForAst(yystack_[5].value.as < xxs::ast_ptr > (), yystack_[4].value.as < xxs::ast_ptr > (), yystack_[2].value.as < xxs::ast_ptr > (), yystack_[0].value.as < xxs::StmtsAst* > ());          }
    break;

  case 11: // stmt: "while" "(" expr_1 ")" block_2
                                                            { yylhs.value.as < xxs::ast_ptr > () = new ForAst(nullptr, yystack_[2].value.as < xxs::ast_ptr > (), nullptr, yystack_[0].value.as < xxs::StmtsAst* > ());}
    break;

  case 12: // block_1: "{" stmts "}"
                                                                                                                                                              { yylhs.value.as < xxs::StmtsAst* > () = yystack_[1].value.as < xxs::StmtsAst* > ();                                    }
    break;

  case 13: // block_1: "{" "}"
                                                                                                                                                                              { yylhs.value.as < xxs::StmtsAst* > () = new StmtsAst();                            }
    break;

  case 14: // block_2: block_1
                                                                                                                                                                              { yylhs.value.as < xxs::StmtsAst* > () = yystack_[0].value.as < xxs::StmtsAst* > (); }
    break;

  case 15: // block_2: stmt
                                                                                                                                                                                      { yylhs.value.as < xxs::StmtsAst* > () = new StmtsAst({ yystack_[0].value.as < xxs::ast_ptr > () });                      }
    break;

  case 16: // for_begin: "for" "(" expr_1 ";"
                                                                                                                        { yylhs.value.as < xxs::ast_ptr > () = yystack_[1].value.as < xxs::ast_ptr > ();                                   }
    break;

  case 17: // for_begin: "for" "(" ";"
                                                                                                                        { yylhs.value.as < xxs::ast_ptr > () = nullptr;                                   }
    break;

  case 18: // for_cond: expr_1
                    { yylhs.value.as < xxs::ast_ptr > () = yystack_[0].value.as < xxs::ast_ptr > (); }
    break;

  case 19: // for_cond: %empty
                    { yylhs.value.as < xxs::ast_ptr > () = nullptr; }
    break;

  case 20: // for_step: expr_1
                    { yylhs.value.as < xxs::ast_ptr > () = yystack_[0].value.as < xxs::ast_ptr > (); }
    break;

  case 21: // for_step: %empty
                    { yylhs.value.as < xxs::ast_ptr > () = nullptr; }
    break;

  case 22: // else_1: %empty
                                                                                                                                                                        { yylhs.value.as < xxs::StmtsAst* > () = new StmtsAst(); 														}
    break;

  case 23: // else_1: "else" block_2
                                                                                                                                                              { yylhs.value.as < xxs::StmtsAst* > () = yystack_[0].value.as < xxs::StmtsAst* > (); 																		    }
    break;

  case 24: // expr_1: "identifier" "=" expr_1
                                                                                                                                        { yylhs.value.as < xxs::ast_ptr > () = new VarAssignAst(yystack_[2].value.as < std::string > (), token::EQ, yystack_[0].value.as < xxs::ast_ptr > ());				}
    break;

  case 25: // expr_1: expr
                                                                                                                                                                                                        { yylhs.value.as < xxs::ast_ptr > () = yystack_[0].value.as < xxs::ast_ptr > (); 																				}
    break;

  case 26: // expr_1: func_begin "(" idents ")" block_1
                                                                                                                                { yylhs.value.as < xxs::ast_ptr > () = new FuncAst(yystack_[4].value.as < std::string > (), M(yystack_[2].value.as < params_t > ()), yystack_[0].value.as < xxs::StmtsAst* > ()); 		}
    break;

  case 27: // func_begin: "function" "identifier"
                                                                                                            { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); 																   			}
    break;

  case 28: // func_begin: "function"
                                                                                                                                                                            { yylhs.value.as < std::string > () = ""; 																   			}
    break;

  case 29: // expr: primary
                                                                                                                                                                        { yylhs.value.as < xxs::ast_ptr > () = yystack_[0].value.as < xxs::ast_ptr > ();                                        }
    break;

  case 30: // expr: "(" expr_1 ")"
                                                                                                                                                                { yylhs.value.as < xxs::ast_ptr > () = yystack_[1].value.as < xxs::ast_ptr > ();                                        }
    break;

  case 31: // expr: expr "(" exprs ")"
                                                                                                                            { yylhs.value.as < xxs::ast_ptr > () = new CallAst(yystack_[3].value.as < xxs::ast_ptr > (), M(yystack_[1].value.as < asts_t > ()));                    }
    break;

  case 32: // expr: expr "+" expr
                                                                                                                                                                { BINARY(PLUS);				                            }
    break;

  case 33: // expr: expr "-" expr
                                                                                                                                                                { BINARY(MINUS);			                          	}
    break;

  case 34: // expr: expr "*" expr
                                                                                                                                                                { BINARY(MUL);				                          	}
    break;

  case 35: // expr: expr "/" expr
                                                                                                                                                                { BINARY(DIV);				                          	}
    break;

  case 36: // expr: expr ">" expr
                                                                                                                                                                { BINARY(GT);					                            }
    break;

  case 37: // expr: expr "<" expr
                                                                                                                                                                { BINARY(LT);					                            }
    break;

  case 38: // expr: expr ">=" expr
                                                                                                                                                                { BINARY(GTE);				                          	}
    break;

  case 39: // expr: expr "<=" expr
                                                                                                                                                                { BINARY(LTE);				                          	}
    break;

  case 40: // expr: expr "==" expr
                                                                                                                                                                { BINARY(EE);					                            }
    break;

  case 41: // expr: expr "!=" expr
                                                                                                                                                                { BINARY(NE);					                            }
    break;

  case 42: // expr: "identifier" "++"
                                                            { yylhs.value.as < xxs::ast_ptr > () = new StmtsAst{{ new VarAccessAst(yystack_[1].value.as < std::string > ()), IPPMM(1, PLUS), }, false}; }
    break;

  case 43: // expr: "identifier" "--"
                                                            { yylhs.value.as < xxs::ast_ptr > () = new StmtsAst{{ new VarAccessAst(yystack_[1].value.as < std::string > ()), IPPMM(1, MINUS) }, false}; }
    break;

  case 44: // expr: "++" "identifier"
                                                            { yylhs.value.as < xxs::ast_ptr > () = IPPMM(0, PLUS);                            }
    break;

  case 45: // expr: "--" "identifier"
                                                            { yylhs.value.as < xxs::ast_ptr > () = IPPMM(0, MINUS);                           }
    break;

  case 46: // primary: "int"
                                                                                                                                                                                      { yylhs.value.as < xxs::ast_ptr > () = new IntAst(yystack_[0].value.as < int > ());		  											}
    break;

  case 47: // primary: "nil"
                                                                                                                                                                                              { yylhs.value.as < xxs::ast_ptr > () = new IntAst(NULL); 													}
    break;

  case 48: // primary: "float"
                                                                                                                                                                                              { yylhs.value.as < xxs::ast_ptr > () = new FloatAst(yystack_[0].value.as < float > ());		 											}
    break;

  case 49: // primary: "identifier"
                                                                                                                                                                                              { yylhs.value.as < xxs::ast_ptr > () = new VarAccessAst(yystack_[0].value.as < std::string > ());                      }
    break;

  case 50: // idents: %empty
                                                                                                                                                                              { yylhs.value.as < params_t > () = params_t(); 										  					}
    break;

  case 51: // idents: "identifier"
                                                                                                                                                                                                      { yylhs.value.as < params_t > () = params_t{yystack_[0].value.as < std::string > ()}; 															}
    break;

  case 52: // idents: idents "," "identifier"
                                                                                                                                              { yylhs.value.as < params_t > () = M(yystack_[2].value.as < params_t > ()); yylhs.value.as < params_t > ().push_back(yystack_[0].value.as < std::string > ()); 					        }
    break;

  case 53: // exprs: %empty
                                                                                                                                                                              { yylhs.value.as < asts_t > () = asts_t(); 											  					}
    break;

  case 54: // exprs: expr_1
                                                                                                                                                                                                    { yylhs.value.as < asts_t > () = asts_t{yystack_[0].value.as < xxs::ast_ptr > ()}; 																}
    break;

  case 55: // exprs: exprs "," expr_1
                                                                                                                                                                                    { yylhs.value.as < asts_t > () = M(yystack_[2].value.as < asts_t > ()); yylhs.value.as < asts_t > ().push_back(yystack_[0].value.as < xxs::ast_ptr > ()); 					        }
    break;



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





  const signed char parser::yypact_ninf_ = -73;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
     166,    -3,     9,   -16,     6,   -73,     7,   -73,   -73,    24,
      28,    36,   177,    53,    58,   -73,   177,    25,    33,   196,
     -73,   -73,   -73,    30,   177,    26,   177,   -73,   -73,   177,
     -73,   -73,    27,   -73,   -73,   -73,    35,   -73,   -73,    59,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     177,   -73,    45,   -73,    43,    47,   -73,   -73,   177,   -73,
      19,    13,   -13,   -13,    51,    51,    -8,    -8,   210,    -8,
      -8,   210,   -73,    20,   140,   -73,   140,    52,   -73,    50,
      68,   -73,   177,    86,   -73,   -73,    75,   -73,   140,   -73,
     -73,   -73,   -73,   113,   140,   -73,   -73,   -73,   -73
  };

  const signed char
  parser::yydefact_[] =
  {
       0,    28,     0,     0,     0,    47,     0,    46,    48,    49,
       0,     0,     0,     0,     0,     3,    19,     5,     0,    25,
      29,    27,     8,     0,     0,     0,     0,    42,    43,     0,
      44,    45,     0,     1,     2,     4,     0,    18,     6,    50,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      53,     7,     0,    17,     0,     0,    24,    30,    21,    51,
       0,    49,    32,    33,    34,    35,    37,    36,    40,    39,
      38,    41,    54,     0,     0,    16,     0,     0,    20,     0,
       0,    31,     0,     0,    15,    14,    22,    11,     0,    26,
      52,    55,    13,     0,     0,     9,    10,    12,    23
  };

  const short
  parser::yypgoto_[] =
  {
     -73,   -73,     2,     0,     8,   -72,   -73,   -73,   -73,   -73,
      -1,   -73,   197,   -73,   -73,   -73
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,    13,    14,    84,    85,    86,    16,    36,    77,    95,
      17,    18,    19,    20,    60,    73
  };

  const signed char
  parser::yytable_[] =
  {
      15,    23,    42,    43,    87,    40,    41,    42,    43,    21,
      24,    32,     1,    50,    35,    37,    96,     5,    50,     7,
       8,     9,    98,    52,    54,    55,    10,    11,    56,     1,
      27,    28,    25,    26,     5,    12,     7,     8,     9,    22,
      30,    27,    28,    10,    11,    29,    79,    81,    31,    72,
      80,    82,    12,    33,    57,    38,    53,    78,    34,    39,
      51,     1,     2,     3,     4,    58,     5,     6,     7,     8,
       9,    59,    74,    75,    76,    10,    11,    50,    83,    88,
      90,    91,    94,    15,    12,    93,     0,    89,     0,     1,
       2,     3,     4,    35,     5,     6,     7,     8,     9,     0,
       0,     0,     0,    10,    11,     0,     0,     0,     0,     0,
       0,     0,    12,     0,     0,    92,     1,     2,     3,     4,
       0,     5,     6,     7,     8,     9,     0,     0,     0,     0,
      10,    11,     0,     0,     0,     0,     0,     0,     0,    12,
       0,     0,    97,     1,     2,     3,     4,     0,     5,     6,
       7,     8,     9,     0,     0,     0,     0,    10,    11,     0,
       0,     0,     0,     0,     0,     0,    12,     0,    83,     1,
       2,     3,     4,     0,     5,     6,     7,     8,     9,     0,
       1,     0,     0,    10,    11,     5,     0,     7,     8,     9,
       0,     0,    12,     0,    10,    11,     5,     0,     7,     8,
      61,     0,     0,    12,     0,    10,    11,     0,     0,    40,
      41,    42,    43,     0,    12,    44,    45,     0,    46,    47,
      48,    49,    50,    40,    41,    42,    43,     0,     0,    44,
      45,     0,     0,    47,    48,     0,    50,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71
  };

  const signed char
  parser::yycheck_[] =
  {
       0,     2,    15,    16,    76,    13,    14,    15,    16,    12,
      26,    12,     3,    26,    14,    16,    88,     8,    26,    10,
      11,    12,    94,    24,    25,    26,    17,    18,    29,     3,
      17,    18,    26,    26,     8,    26,    10,    11,    12,    30,
      12,    17,    18,    17,    18,    21,    27,    27,    12,    50,
      31,    31,    26,     0,    27,    30,    30,    58,     0,    26,
      30,     3,     4,     5,     6,    30,     8,     9,    10,    11,
      12,    12,    27,    30,    27,    17,    18,    26,    28,    27,
      12,    82,     7,    83,    26,    83,    -1,    79,    -1,     3,
       4,     5,     6,    93,     8,     9,    10,    11,    12,    -1,
      -1,    -1,    -1,    17,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    26,    -1,    -1,    29,     3,     4,     5,     6,
      -1,     8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,
      17,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      -1,    -1,    29,     3,     4,     5,     6,    -1,     8,     9,
      10,    11,    12,    -1,    -1,    -1,    -1,    17,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    26,    -1,    28,     3,
       4,     5,     6,    -1,     8,     9,    10,    11,    12,    -1,
       3,    -1,    -1,    17,    18,     8,    -1,    10,    11,    12,
      -1,    -1,    26,    -1,    17,    18,     8,    -1,    10,    11,
      12,    -1,    -1,    26,    -1,    17,    18,    -1,    -1,    13,
      14,    15,    16,    -1,    26,    19,    20,    -1,    22,    23,
      24,    25,    26,    13,    14,    15,    16,    -1,    -1,    19,
      20,    -1,    -1,    23,    24,    -1,    26,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49
  };

  const signed char
  parser::yystos_[] =
  {
       0,     3,     4,     5,     6,     8,     9,    10,    11,    12,
      17,    18,    26,    34,    35,    36,    39,    43,    44,    45,
      46,    12,    30,    43,    26,    26,    26,    17,    18,    21,
      12,    12,    43,     0,     0,    36,    40,    43,    30,    26,
      13,    14,    15,    16,    19,    20,    22,    23,    24,    25,
      26,    30,    43,    30,    43,    43,    43,    27,    30,    12,
      47,    12,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    45,    43,    48,    27,    30,    27,    41,    43,    27,
      31,    27,    31,    28,    36,    37,    38,    38,    27,    37,
      12,    43,    29,    35,     7,    42,    38,    29,    38
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    33,    34,    35,    35,    36,    36,    36,    36,    36,
      36,    36,    37,    37,    38,    38,    39,    39,    40,    40,
      41,    41,    42,    42,    43,    43,    43,    44,    44,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    46,    46,    46,    46,
      47,    47,    47,    48,    48,    48
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     1,     2,     1,     2,     3,     2,     6,
       6,     5,     3,     2,     1,     1,     4,     3,     1,     0,
       1,     0,     0,     2,     3,     1,     5,     2,     1,     1,
       3,     4,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     2,     1,     1,     1,     1,
       0,     1,     3,     0,     1,     3
  };


#if XXSDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"function\"",
  "\"return\"", "\"if\"", "\"for\"", "\"else\"", "\"nil\"", "\"while\"",
  "\"int\"", "\"float\"", "\"identifier\"", "\"+\"", "\"-\"", "\"*\"",
  "\"/\"", "\"++\"", "\"--\"", "\"<\"", "\">\"", "\"=\"", "\"==\"",
  "\"<=\"", "\">=\"", "\"!=\"", "\"(\"", "\")\"", "\"{\"", "\"}\"",
  "\";\"", "\",\"", "\">>\"", "$accept", "main", "stmts", "stmt",
  "block_1", "block_2", "for_begin", "for_cond", "for_step", "else_1",
  "expr_1", "func_begin", "expr", "primary", "idents", "exprs", YY_NULLPTR
  };
#endif


#if XXSDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,    63,    63,    66,    67,    71,    72,    73,    74,    75,
      76,    77,    80,    81,    84,    85,    89,    90,    93,    94,
      97,    98,   101,   102,   105,   106,   107,   110,   111,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   133,   134,   135,   136,
     139,   140,   141,   144,   145,   146
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



#undef M
#undef BINARY
#undef IPPMM

void xxs::parser::error(const location_type& loc, const std::string& msg)
{
  throw xxs::syntax_error(loc);
}
