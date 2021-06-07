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
#line 26 "parser.y"

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
  parser::parser (xxs::FunctionAst *& program_yyarg)
#if XXSDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      program (program_yyarg)
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
      case symbol_kind::S_then_1: // then_1
      case symbol_kind::S_else_1: // else_1
      case symbol_kind::S_func_end: // func_end
        value.YY_MOVE_OR_COPY< xxs::StmtsAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
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
      case symbol_kind::S_then_1: // then_1
      case symbol_kind::S_else_1: // else_1
      case symbol_kind::S_func_end: // func_end
        value.move< xxs::StmtsAst* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
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
      case symbol_kind::S_then_1: // then_1
      case symbol_kind::S_else_1: // else_1
      case symbol_kind::S_func_end: // func_end
        value.copy< xxs::StmtsAst* > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
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
      case symbol_kind::S_then_1: // then_1
      case symbol_kind::S_else_1: // else_1
      case symbol_kind::S_func_end: // func_end
        value.move< xxs::StmtsAst* > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
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
      case symbol_kind::S_then_1: // then_1
      case symbol_kind::S_else_1: // else_1
      case symbol_kind::S_func_end: // func_end
        yylhs.value.emplace< xxs::StmtsAst* > ();
        break;

      case symbol_kind::S_stmt: // stmt
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
#line 58 "parser.y"
                  {  program = new FunctionAst("__main", params_t(), yystack_[1].value.as < xxs::StmtsAst* > ()); }
#line 716 "parser.cpp"
    break;

  case 3: // stmts: stmt
#line 61 "parser.y"
                                                { yylhs.value.as < xxs::StmtsAst* > () = new StmtsAst(); yylhs.value.as < xxs::StmtsAst* > ()->push(yystack_[0].value.as < xxs::ast_ptr > ()); }
#line 722 "parser.cpp"
    break;

  case 4: // stmts: stmts stmt
#line 62 "parser.y"
                                                 { yylhs.value.as < xxs::StmtsAst* > () = yystack_[1].value.as < xxs::StmtsAst* > (); yylhs.value.as < xxs::StmtsAst* > ()->push(yystack_[0].value.as < xxs::ast_ptr > ()); }
#line 728 "parser.cpp"
    break;

  case 5: // stmt: expr_1 ";"
#line 65 "parser.y"
                                                                                                        { yylhs.value.as < xxs::ast_ptr > () = yystack_[1].value.as < xxs::ast_ptr > (); }
#line 734 "parser.cpp"
    break;

  case 6: // stmt: expr_1
#line 66 "parser.y"
                                                                                                                                { yylhs.value.as < xxs::ast_ptr > () = yystack_[0].value.as < xxs::ast_ptr > (); }
#line 740 "parser.cpp"
    break;

  case 7: // stmt: "identifier" "=" expr_1 ";"
#line 67 "parser.y"
                                                                                { yylhs.value.as < xxs::ast_ptr > () = new VarAssignAst(yystack_[3].value.as < std::string > (), token::EQ, yystack_[1].value.as < xxs::ast_ptr > ());}
#line 746 "parser.cpp"
    break;

  case 8: // stmt: "return" expr_1 ";"
#line 68 "parser.y"
                                                                                { yylhs.value.as < xxs::ast_ptr > () = new RetAst(yystack_[1].value.as < xxs::ast_ptr > ()); }
#line 752 "parser.cpp"
    break;

  case 9: // stmt: "return" ";"
#line 69 "parser.y"
                                                                                                        { yylhs.value.as < xxs::ast_ptr > () = new RetAst(); }
#line 758 "parser.cpp"
    break;

  case 10: // stmt: "if" "(" expr ")" then_1 else_1
#line 70 "parser.y"
                                                        { yylhs.value.as < xxs::ast_ptr > () = new IfAst(yystack_[3].value.as < xxs::ast_ptr > (), yystack_[1].value.as < xxs::StmtsAst* > (), yystack_[0].value.as < xxs::StmtsAst* > ()); }
#line 764 "parser.cpp"
    break;

  case 11: // then_1: "{" stmts "}"
#line 73 "parser.y"
                          { yylhs.value.as < xxs::StmtsAst* > () = yystack_[1].value.as < xxs::StmtsAst* > (); 						   }
#line 770 "parser.cpp"
    break;

  case 12: // then_1: "{" "}"
#line 74 "parser.y"
                                                      { yylhs.value.as < xxs::StmtsAst* > () = new StmtsAst();   }
#line 776 "parser.cpp"
    break;

  case 13: // then_1: stmt
#line 75 "parser.y"
                                                                                {	yylhs.value.as < xxs::StmtsAst* > () = new StmtsAst({yystack_[0].value.as < xxs::ast_ptr > ()}); }
#line 782 "parser.cpp"
    break;

  case 14: // else_1: %empty
#line 78 "parser.y"
                                                                                { yylhs.value.as < xxs::StmtsAst* > () = new StmtsAst(); 				}
#line 788 "parser.cpp"
    break;

  case 15: // else_1: "else" "{" stmts "}"
#line 79 "parser.y"
                                                { yylhs.value.as < xxs::StmtsAst* > () = yystack_[1].value.as < xxs::StmtsAst* > (); 								}
#line 794 "parser.cpp"
    break;

  case 16: // else_1: "else" "{" "}"
#line 80 "parser.y"
                                                        { yylhs.value.as < xxs::StmtsAst* > () = new StmtsAst();  			}
#line 800 "parser.cpp"
    break;

  case 17: // else_1: "else" stmt
#line 81 "parser.y"
                                                                                        { yylhs.value.as < xxs::StmtsAst* > () = new StmtsAst({yystack_[0].value.as < xxs::ast_ptr > ()}); }
#line 806 "parser.cpp"
    break;

  case 18: // expr_1: expr
#line 84 "parser.y"
                                                                                                                        { yylhs.value.as < xxs::ast_ptr > () = yystack_[0].value.as < xxs::ast_ptr > (); 																		 }
#line 812 "parser.cpp"
    break;

  case 19: // expr_1: func_begin idents func_end
#line 85 "parser.y"
                                                                        { yylhs.value.as < xxs::ast_ptr > () = new FunctionAst(yystack_[2].value.as < std::string > (), std::move(yystack_[1].value.as < params_t > ()), yystack_[0].value.as < xxs::StmtsAst* > ()); }
#line 818 "parser.cpp"
    break;

  case 20: // func_begin: "function" "identifier" "("
#line 88 "parser.y"
                                          { yylhs.value.as < std::string > () = yystack_[1].value.as < std::string > (); 						}
#line 824 "parser.cpp"
    break;

  case 21: // func_begin: "function" "("
#line 89 "parser.y"
                                                                                                { yylhs.value.as < std::string > () = ""; 						}
#line 830 "parser.cpp"
    break;

  case 22: // func_end: ")" "{" stmts "}"
#line 92 "parser.y"
                                                                        { yylhs.value.as < xxs::StmtsAst* > () = yystack_[1].value.as < xxs::StmtsAst* > (); 				 }
#line 836 "parser.cpp"
    break;

  case 23: // func_end: ")" "{" "}"
#line 93 "parser.y"
                                                                                                                { yylhs.value.as < xxs::StmtsAst* > () = new StmtsAst(); }
#line 842 "parser.cpp"
    break;

  case 24: // expr: primary
#line 96 "parser.y"
                                                                                                                { yylhs.value.as < xxs::ast_ptr > () = yystack_[0].value.as < xxs::ast_ptr > ();															}
#line 848 "parser.cpp"
    break;

  case 25: // expr: "(" expr_1 ")"
#line 97 "parser.y"
                                                                                                        { yylhs.value.as < xxs::ast_ptr > () = yystack_[1].value.as < xxs::ast_ptr > (); 															}
#line 854 "parser.cpp"
    break;

  case 26: // expr: expr "(" exprs ")"
#line 98 "parser.y"
                                                                { yylhs.value.as < xxs::ast_ptr > () = new CallAst(yystack_[3].value.as < xxs::ast_ptr > (), std::move(yystack_[1].value.as < asts_t > ())); 	}
#line 860 "parser.cpp"
    break;

  case 27: // expr: expr "+" expr
#line 99 "parser.y"
                                                                                                        { yylhs.value.as < xxs::ast_ptr > () = new BinaryAst(token::PLUS, yystack_[2].value.as < xxs::ast_ptr > (), yystack_[0].value.as < xxs::ast_ptr > ());		}
#line 866 "parser.cpp"
    break;

  case 28: // expr: expr "-" expr
#line 100 "parser.y"
                                                                                                        { yylhs.value.as < xxs::ast_ptr > () = new BinaryAst(token::MINUS, yystack_[2].value.as < xxs::ast_ptr > (), yystack_[0].value.as < xxs::ast_ptr > ());		}
#line 872 "parser.cpp"
    break;

  case 29: // expr: expr "*" expr
#line 101 "parser.y"
                                                                                                        { yylhs.value.as < xxs::ast_ptr > () = new BinaryAst(token::MUL, yystack_[2].value.as < xxs::ast_ptr > (), yystack_[0].value.as < xxs::ast_ptr > ());			}
#line 878 "parser.cpp"
    break;

  case 30: // expr: expr "/" expr
#line 102 "parser.y"
                                                                                                        { yylhs.value.as < xxs::ast_ptr > () = new BinaryAst(token::DIV, yystack_[2].value.as < xxs::ast_ptr > (), yystack_[0].value.as < xxs::ast_ptr > ());			}
#line 884 "parser.cpp"
    break;

  case 31: // expr: expr ">" expr
#line 103 "parser.y"
                                                                                                        { yylhs.value.as < xxs::ast_ptr > () = new BinaryAst(token::GT, yystack_[2].value.as < xxs::ast_ptr > (), yystack_[0].value.as < xxs::ast_ptr > ());			}
#line 890 "parser.cpp"
    break;

  case 32: // expr: expr "<" expr
#line 104 "parser.y"
                                                                                                        { yylhs.value.as < xxs::ast_ptr > () = new BinaryAst(token::LT, yystack_[2].value.as < xxs::ast_ptr > (), yystack_[0].value.as < xxs::ast_ptr > ());			}
#line 896 "parser.cpp"
    break;

  case 33: // expr: expr ">=" expr
#line 105 "parser.y"
                                                                                                        { yylhs.value.as < xxs::ast_ptr > () = new BinaryAst(token::GTE, yystack_[2].value.as < xxs::ast_ptr > (), yystack_[0].value.as < xxs::ast_ptr > ());			}
#line 902 "parser.cpp"
    break;

  case 34: // expr: expr "<=" expr
#line 106 "parser.y"
                                                                                                        { yylhs.value.as < xxs::ast_ptr > () = new BinaryAst(token::LTE, yystack_[2].value.as < xxs::ast_ptr > (), yystack_[0].value.as < xxs::ast_ptr > ());			}
#line 908 "parser.cpp"
    break;

  case 35: // expr: expr "==" expr
#line 107 "parser.y"
                                                                                                        { yylhs.value.as < xxs::ast_ptr > () = new BinaryAst(token::EE, yystack_[2].value.as < xxs::ast_ptr > (), yystack_[0].value.as < xxs::ast_ptr > ());			}
#line 914 "parser.cpp"
    break;

  case 36: // expr: expr "!=" expr
#line 108 "parser.y"
                                                                                                        { yylhs.value.as < xxs::ast_ptr > () = new BinaryAst(token::NE, yystack_[2].value.as < xxs::ast_ptr > (), yystack_[0].value.as < xxs::ast_ptr > ());			}
#line 920 "parser.cpp"
    break;

  case 37: // primary: "int"
#line 111 "parser.y"
                                                { yylhs.value.as < xxs::ast_ptr > () = new IntAst(yystack_[0].value.as < int > ());		  	}
#line 926 "parser.cpp"
    break;

  case 38: // primary: "nil"
#line 112 "parser.y"
                                                        { yylhs.value.as < xxs::ast_ptr > () = new IntAst(NULL); 			}
#line 932 "parser.cpp"
    break;

  case 39: // primary: "float"
#line 113 "parser.y"
                                                        { yylhs.value.as < xxs::ast_ptr > () = new FloatAst(yystack_[0].value.as < float > ());		 	}
#line 938 "parser.cpp"
    break;

  case 40: // primary: "identifier"
#line 114 "parser.y"
                                                        { yylhs.value.as < xxs::ast_ptr > () = new VarAccessAst(yystack_[0].value.as < std::string > ());	}
#line 944 "parser.cpp"
    break;

  case 41: // idents: %empty
#line 117 "parser.y"
                                                        { yylhs.value.as < params_t > () = params_t(); 										  }
#line 950 "parser.cpp"
    break;

  case 42: // idents: "identifier"
#line 118 "parser.y"
                                                                                { yylhs.value.as < params_t > () = params_t{yystack_[0].value.as < std::string > ()}; 										}
#line 956 "parser.cpp"
    break;

  case 43: // idents: idents "," "identifier"
#line 119 "parser.y"
                                                  { yylhs.value.as < params_t > () = std::move(yystack_[2].value.as < params_t > ()); yylhs.value.as < params_t > ().push_back(yystack_[0].value.as < std::string > ()); }
#line 962 "parser.cpp"
    break;

  case 44: // exprs: %empty
#line 122 "parser.y"
                                                { yylhs.value.as < asts_t > () = asts_t(); 											  }
#line 968 "parser.cpp"
    break;

  case 45: // exprs: expr
#line 123 "parser.y"
                                                                        { yylhs.value.as < asts_t > () = asts_t{yystack_[0].value.as < xxs::ast_ptr > ()}; 											}
#line 974 "parser.cpp"
    break;

  case 46: // exprs: exprs "," expr
#line 124 "parser.y"
                                                { yylhs.value.as < asts_t > () = std::move(yystack_[2].value.as < asts_t > ()); yylhs.value.as < asts_t > ().push_back(yystack_[0].value.as < xxs::ast_ptr > ()); }
#line 980 "parser.cpp"
    break;


#line 984 "parser.cpp"

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





  const signed char parser::yypact_ninf_ = -21;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
     166,    32,    -1,   -18,   -21,   -21,   -21,   -14,   176,     5,
      23,   -21,    -4,    14,   207,   -21,     7,   -21,   -21,   -21,
      21,   182,   176,    29,   -21,   -21,   -21,   -21,   -21,    39,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     182,   -21,   -21,   194,    33,   -21,    44,    45,   -21,    36,
      36,    58,    58,    81,    81,   219,    81,    81,   219,   207,
      40,   136,   -21,    31,   -21,   -21,   182,    66,   -21,    79,
     -21,    74,   207,   -21,    97,   158,   -21,   -21,   -21,   105,
     -21,   -21,   128,   -21
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,    38,    37,    39,    40,     0,     0,
       0,     3,     6,    41,    18,    24,     0,    21,    40,     9,
       0,     0,     0,     0,     1,     2,     4,     5,    42,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      44,    20,     8,     0,     0,    25,     0,     0,    19,    27,
      28,    29,    30,    32,    31,    35,    34,    33,    36,    45,
       0,     0,     7,     0,    43,    26,     0,     0,    13,    14,
      23,     0,    46,    12,     0,     0,    10,    22,    11,     0,
      17,    16,     0,    15
  };

  const signed char
  parser::yypgoto_[] =
  {
     -21,   -21,   -19,   -10,   -21,   -21,    35,   -21,   -21,   -20,
     -21,   -21,   -21
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     9,    10,    11,    69,    76,    12,    13,    48,    14,
      15,    29,    60
  };

  const signed char
  parser::yytable_[] =
  {
      26,    43,     1,    22,    21,    24,     4,     5,     6,    18,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,     8,    27,    25,    28,    19,     1,     2,     3,    41,
       4,     5,     6,     7,     1,     2,     3,    20,     4,     5,
       6,     7,    16,    23,    71,     8,    72,    42,    74,    32,
      33,    68,    45,     8,    17,    64,    70,    44,    40,    62,
      82,    26,    46,    65,    26,    80,    47,    66,    63,     1,
       2,     3,    26,     4,     5,     6,     7,     1,     2,     3,
      40,     4,     5,     6,     7,    75,     0,     0,     8,     0,
       0,    73,    30,    31,    32,    33,     8,     0,     0,    77,
       1,     2,     3,    40,     4,     5,     6,     7,     1,     2,
       3,     0,     4,     5,     6,     7,     0,     0,     0,     8,
       0,     0,    78,     0,     0,     0,     0,     8,     0,     0,
      81,     1,     2,     3,     0,     4,     5,     6,     7,     1,
       2,     3,     0,     4,     5,     6,     7,     0,     0,     0,
       8,     0,     0,    83,     0,     0,     0,     0,     8,     0,
      67,     1,     2,     3,     0,     4,     5,     6,     7,     1,
       2,     3,     0,     4,     5,     6,     7,     0,     0,     1,
       8,     0,    79,     4,     5,     6,    18,     0,     8,     4,
       5,     6,    18,     0,     0,     0,     0,     0,     8,     0,
       0,     0,     0,     0,     8,    30,    31,    32,    33,    34,
      35,     0,    36,    37,    38,    39,    40,    61,    30,    31,
      32,    33,    34,    35,     0,    36,    37,    38,    39,    40,
      30,    31,    32,    33,    34,    35,     0,     0,    37,    38,
       0,    40
  };

  const signed char
  parser::yycheck_[] =
  {
      10,    21,     3,    17,    22,     0,     7,     8,     9,    10,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    22,    26,     0,    10,    26,     3,     4,     5,    22,
       7,     8,     9,    10,     3,     4,     5,     2,     7,     8,
       9,    10,    10,     8,    63,    22,    66,    26,    67,    13,
      14,    61,    23,    22,    22,    10,    25,    22,    22,    26,
      79,    71,    23,    23,    74,    75,    27,    27,    24,     3,
       4,     5,    82,     7,     8,     9,    10,     3,     4,     5,
      22,     7,     8,     9,    10,     6,    -1,    -1,    22,    -1,
      -1,    25,    11,    12,    13,    14,    22,    -1,    -1,    25,
       3,     4,     5,    22,     7,     8,     9,    10,     3,     4,
       5,    -1,     7,     8,     9,    10,    -1,    -1,    -1,    22,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    22,    -1,    -1,
      25,     3,     4,     5,    -1,     7,     8,     9,    10,     3,
       4,     5,    -1,     7,     8,     9,    10,    -1,    -1,    -1,
      22,    -1,    -1,    25,    -1,    -1,    -1,    -1,    22,    -1,
      24,     3,     4,     5,    -1,     7,     8,     9,    10,     3,
       4,     5,    -1,     7,     8,     9,    10,    -1,    -1,     3,
      22,    -1,    24,     7,     8,     9,    10,    -1,    22,     7,
       8,     9,    10,    -1,    -1,    -1,    -1,    -1,    22,    -1,
      -1,    -1,    -1,    -1,    22,    11,    12,    13,    14,    15,
      16,    -1,    18,    19,    20,    21,    22,    23,    11,    12,
      13,    14,    15,    16,    -1,    18,    19,    20,    21,    22,
      11,    12,    13,    14,    15,    16,    -1,    -1,    19,    20,
      -1,    22
  };

  const signed char
  parser::yystos_[] =
  {
       0,     3,     4,     5,     7,     8,     9,    10,    22,    30,
      31,    32,    35,    36,    38,    39,    10,    22,    10,    26,
      35,    22,    17,    35,     0,     0,    32,    26,    10,    40,
      11,    12,    13,    14,    15,    16,    18,    19,    20,    21,
      22,    22,    26,    38,    35,    23,    23,    27,    37,    38,
      38,    38,    38,    38,    38,    38,    38,    38,    38,    38,
      41,    23,    26,    24,    10,    23,    27,    24,    32,    33,
      25,    31,    38,    25,    31,     6,    34,    25,    25,    24,
      32,    25,    31,    25
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    29,    30,    31,    31,    32,    32,    32,    32,    32,
      32,    33,    33,    33,    34,    34,    34,    34,    35,    35,
      36,    36,    37,    37,    38,    38,    38,    38,    38,    38,
      38,    38,    38,    38,    38,    38,    38,    39,    39,    39,
      39,    40,    40,    40,    41,    41,    41
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     1,     2,     2,     1,     4,     3,     2,
       6,     3,     2,     1,     0,     4,     3,     2,     1,     3,
       3,     2,     4,     3,     1,     3,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     0,     1,     3,     0,     1,     3
  };


#if XXSDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"function\"",
  "\"return\"", "\"if\"", "\"else\"", "\"nil\"", "\"int\"", "\"float\"",
  "\"identifier\"", "\"+\"", "\"-\"", "\"*\"", "\"/\"", "\"<\"", "\">\"",
  "\"=\"", "\"==\"", "\"<=\"", "\">=\"", "\"!=\"", "\"(\"", "\")\"",
  "\"{\"", "\"}\"", "\";\"", "\",\"", "\">>\"", "$accept", "main", "stmts",
  "stmt", "then_1", "else_1", "expr_1", "func_begin", "func_end", "expr",
  "primary", "idents", "exprs", YY_NULLPTR
  };
#endif


#if XXSDEBUG
  const signed char
  parser::yyrline_[] =
  {
       0,    58,    58,    61,    62,    65,    66,    67,    68,    69,
      70,    73,    74,    75,    78,    79,    80,    81,    84,    85,
      88,    89,    92,    93,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   111,   112,   113,
     114,   117,   118,   119,   122,   123,   124
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
#line 1371 "parser.cpp"

#line 127 "parser.y"


void xxs::parser::error(const location_type& loc, const std::string& msg)
{
	throw xxs::syntax_error(loc);
}
