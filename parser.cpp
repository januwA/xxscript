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
        value.YY_MOVE_OR_COPY< ASTS > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_idents: // idents
        value.YY_MOVE_OR_COPY< PARAMS > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_expr: // expr
        value.YY_MOVE_OR_COPY< PAST > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT: // "float"
        value.YY_MOVE_OR_COPY< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // "int"
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENT: // "identifier"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
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
        value.move< ASTS > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_idents: // idents
        value.move< PARAMS > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_expr: // expr
        value.move< PAST > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT: // "float"
        value.move< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // "int"
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENT: // "identifier"
        value.move< std::string > (YY_MOVE (that.value));
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
        value.copy< ASTS > (that.value);
        break;

      case symbol_kind::S_idents: // idents
        value.copy< PARAMS > (that.value);
        break;

      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_expr: // expr
        value.copy< PAST > (that.value);
        break;

      case symbol_kind::S_FLOAT: // "float"
        value.copy< float > (that.value);
        break;

      case symbol_kind::S_INT: // "int"
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_IDENT: // "identifier"
        value.copy< std::string > (that.value);
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
        value.move< ASTS > (that.value);
        break;

      case symbol_kind::S_idents: // idents
        value.move< PARAMS > (that.value);
        break;

      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_expr: // expr
        value.move< PAST > (that.value);
        break;

      case symbol_kind::S_FLOAT: // "float"
        value.move< float > (that.value);
        break;

      case symbol_kind::S_INT: // "int"
        value.move< int > (that.value);
        break;

      case symbol_kind::S_IDENT: // "identifier"
        value.move< std::string > (that.value);
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
        yylhs.value.emplace< ASTS > ();
        break;

      case symbol_kind::S_idents: // idents
        yylhs.value.emplace< PARAMS > ();
        break;

      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_expr: // expr
        yylhs.value.emplace< PAST > ();
        break;

      case symbol_kind::S_FLOAT: // "float"
        yylhs.value.emplace< float > ();
        break;

      case symbol_kind::S_INT: // "int"
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_IDENT: // "identifier"
        yylhs.value.emplace< std::string > ();
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
                  {
	 program = new FunctionAst("__main", PARAMS(), yystack_[1].value.as < PAST > ());
}
    break;

  case 3: // stmts: stmt
                                 { yylhs.value.as < PAST > () = new BlockAst(); reinterpret_cast<BlockAst*>(yylhs.value.as < PAST > ())->push(yystack_[0].value.as < PAST > ()); }
    break;

  case 4: // stmts: stmts stmt
                                 { yylhs.value.as < PAST > () = yystack_[1].value.as < PAST > (); reinterpret_cast<BlockAst*>(yylhs.value.as < PAST > ())->push(yystack_[0].value.as < PAST > ()); }
    break;

  case 5: // stmt: expr ";"
                                        { yylhs.value.as < PAST > () = yystack_[1].value.as < PAST > (); }
    break;

  case 6: // stmt: expr
                                                                { yylhs.value.as < PAST > () = yystack_[0].value.as < PAST > (); }
    break;

  case 7: // stmt: "identifier" "=" expr ";"
                      { yylhs.value.as < PAST > () = new VarAssignAst(yystack_[3].value.as < std::string > (), token::EQ, yystack_[1].value.as < PAST > ());}
    break;

  case 8: // stmt: "return" expr ";"
                      { yylhs.value.as < PAST > () = new RetAst(yystack_[1].value.as < PAST > ()); }
    break;

  case 9: // stmt: "return" ";"
                                      { yylhs.value.as < PAST > () = new RetAst(); }
    break;

  case 10: // expr: "int"
          { yylhs.value.as < PAST > () = new IntAst(yystack_[0].value.as < int > ()); }
    break;

  case 11: // expr: "nil"
        { yylhs.value.as < PAST > () = new IntAst(NULL); }
    break;

  case 12: // expr: "float"
        { yylhs.value.as < PAST > () = new FloatAst(yystack_[0].value.as < float > ()); }
    break;

  case 13: // expr: "identifier"
        { yylhs.value.as < PAST > () = new VarAccessAst(yystack_[0].value.as < std::string > ()); }
    break;

  case 14: // expr: "(" expr ")"
                  {yylhs.value.as < PAST > () = yystack_[1].value.as < PAST > ();}
    break;

  case 15: // expr: "function" "identifier" "(" idents ")" "{" stmts "}"
                                                        { yylhs.value.as < PAST > () = new FunctionAst(yystack_[6].value.as < std::string > (), std::move(yystack_[4].value.as < PARAMS > ()), yystack_[1].value.as < PAST > ()); }
    break;

  case 16: // expr: "function" "identifier" "(" idents ")" "{" "}"
                                                  { yylhs.value.as < PAST > () = new FunctionAst(yystack_[5].value.as < std::string > (), std::move(yystack_[3].value.as < PARAMS > ()), new BlockAst()); }
    break;

  case 17: // expr: "function" "(" idents ")" "{" stmts "}"
                                                  { yylhs.value.as < PAST > () = new FunctionAst(std::move(yystack_[4].value.as < PARAMS > ()), yystack_[1].value.as < PAST > ()); }
    break;

  case 18: // expr: "function" "(" idents ")" "{" "}"
                                            { yylhs.value.as < PAST > () = new FunctionAst(std::move(yystack_[3].value.as < PARAMS > ()), new BlockAst()); }
    break;

  case 19: // expr: expr "(" exprs ")"
                                       { yylhs.value.as < PAST > () = new CallAst(yystack_[3].value.as < PAST > (), std::move(yystack_[1].value.as < ASTS > ())); }
    break;

  case 20: // expr: expr "+" expr
                {yylhs.value.as < PAST > () = new BinaryAst(token::PLUS, yystack_[2].value.as < PAST > (), yystack_[0].value.as < PAST > ());}
    break;

  case 21: // expr: expr "-" expr
                {yylhs.value.as < PAST > () = new BinaryAst(token::MINUS, yystack_[2].value.as < PAST > (), yystack_[0].value.as < PAST > ());}
    break;

  case 22: // expr: expr "*" expr
                {yylhs.value.as < PAST > () = new BinaryAst(token::MUL, yystack_[2].value.as < PAST > (), yystack_[0].value.as < PAST > ());}
    break;

  case 23: // expr: expr "/" expr
                {yylhs.value.as < PAST > () = new BinaryAst(token::DIV, yystack_[2].value.as < PAST > (), yystack_[0].value.as < PAST > ());}
    break;

  case 24: // idents: %empty
               { yylhs.value.as < PARAMS > () = PARAMS(); }
    break;

  case 25: // idents: "identifier"
              { yylhs.value.as < PARAMS > () = PARAMS{yystack_[0].value.as < std::string > ()}; }
    break;

  case 26: // idents: idents "," "identifier"
                         { yylhs.value.as < PARAMS > () = std::move(yystack_[2].value.as < PARAMS > ()); yylhs.value.as < PARAMS > ().push_back(yystack_[0].value.as < std::string > ()); }
    break;

  case 27: // exprs: %empty
               { yylhs.value.as < ASTS > () = ASTS(); }
    break;

  case 28: // exprs: expr
       { yylhs.value.as < ASTS > () = ASTS{yystack_[0].value.as < PAST > ()}; }
    break;

  case 29: // exprs: exprs "," expr
                       { yylhs.value.as < ASTS > () = std::move(yystack_[2].value.as < ASTS > ()); yylhs.value.as < ASTS > ().push_back(yystack_[0].value.as < PAST > ()); }
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





  const signed char parser::yypact_ninf_ = -46;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
     100,    -7,     4,   -46,   -46,   -46,   -13,   108,    10,    28,
     -46,   112,    -4,     9,   -46,   -46,   128,   108,   149,   -46,
     -46,   -46,   108,   108,   108,   108,   108,   -46,     9,   -46,
       6,   -46,   133,   -46,    -5,    -5,    -2,    -2,   153,    19,
      40,     3,    24,   -46,   -46,   108,    15,    44,   -46,   153,
      52,   -46,    72,   -46,    80,   -46,   -46
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,    11,    10,    12,    13,     0,     0,     0,
       3,     6,     0,    24,    13,     9,     0,     0,     0,     1,
       2,     4,     0,     0,     0,     0,    27,     5,    24,    25,
       0,     8,     0,    14,    20,    21,    22,    23,    28,     0,
       0,     0,     0,     7,    19,     0,     0,     0,    26,    29,
       0,    18,     0,    16,     0,    17,    15
  };

  const signed char
  parser::yypgoto_[] =
  {
     -46,   -46,   -45,    -9,    -1,    12,   -46
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     8,     9,    10,    11,    30,    39
  };

  const signed char
  parser::yytable_[] =
  {
      21,    16,    52,    12,    17,    54,    18,     1,    24,    25,
      19,     3,     4,     5,    14,    13,    32,    26,    28,    29,
      26,    34,    35,    36,    37,    38,     7,    47,    20,    41,
      15,     1,     2,    42,    48,     3,     4,     5,     6,    50,
      40,     0,    44,    21,    49,    21,    45,     1,     2,     0,
       7,     3,     4,     5,     6,     1,     2,     0,     0,     3,
       4,     5,     6,    46,     0,     0,     7,    42,     0,    51,
       0,     0,     0,     0,     7,     1,     2,    53,     0,     3,
       4,     5,     6,     1,     2,     0,     0,     3,     4,     5,
       6,     0,     0,     0,     7,     0,     0,    55,     0,     0,
       0,     0,     7,     1,     2,    56,     0,     3,     4,     5,
       6,     1,     0,     0,     0,     3,     4,     5,    14,     0,
       0,     0,     7,    22,    23,    24,    25,     0,     0,     0,
       7,     0,     0,     0,    26,     0,     0,     0,    27,    22,
      23,    24,    25,     0,    22,    23,    24,    25,     0,     0,
      26,     0,     0,     0,    31,    26,     0,     0,     0,    43,
      22,    23,    24,    25,    22,    23,    24,    25,     0,     0,
       0,    26,    33,     0,     0,    26
  };

  const signed char
  parser::yycheck_[] =
  {
       9,     2,    47,    10,    17,    50,     7,     3,    13,    14,
       0,     7,     8,     9,    10,    22,    17,    22,    22,    10,
      22,    22,    23,    24,    25,    26,    22,    24,     0,    23,
      26,     3,     4,    27,    10,     7,     8,     9,    10,    24,
      28,    -1,    23,    52,    45,    54,    27,     3,     4,    -1,
      22,     7,     8,     9,    10,     3,     4,    -1,    -1,     7,
       8,     9,    10,    23,    -1,    -1,    22,    27,    -1,    25,
      -1,    -1,    -1,    -1,    22,     3,     4,    25,    -1,     7,
       8,     9,    10,     3,     4,    -1,    -1,     7,     8,     9,
      10,    -1,    -1,    -1,    22,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    22,     3,     4,    25,    -1,     7,     8,     9,
      10,     3,    -1,    -1,    -1,     7,     8,     9,    10,    -1,
      -1,    -1,    22,    11,    12,    13,    14,    -1,    -1,    -1,
      22,    -1,    -1,    -1,    22,    -1,    -1,    -1,    26,    11,
      12,    13,    14,    -1,    11,    12,    13,    14,    -1,    -1,
      22,    -1,    -1,    -1,    26,    22,    -1,    -1,    -1,    26,
      11,    12,    13,    14,    11,    12,    13,    14,    -1,    -1,
      -1,    22,    23,    -1,    -1,    22
  };

  const signed char
  parser::yystos_[] =
  {
       0,     3,     4,     7,     8,     9,    10,    22,    30,    31,
      32,    33,    10,    22,    10,    26,    33,    17,    33,     0,
       0,    32,    11,    12,    13,    14,    22,    26,    22,    10,
      34,    26,    33,    23,    33,    33,    33,    33,    33,    35,
      34,    23,    27,    26,    23,    27,    23,    24,    10,    33,
      24,    25,    31,    25,    31,    25,    25
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    29,    30,    31,    31,    32,    32,    32,    32,    32,
      33,    33,    33,    33,    33,    33,    33,    33,    33,    33,
      33,    33,    33,    33,    34,    34,    34,    35,    35,    35
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     1,     2,     2,     1,     4,     3,     2,
       1,     1,     1,     1,     3,     8,     7,     7,     6,     4,
       3,     3,     3,     3,     0,     1,     3,     0,     1,     3
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
  "stmt", "expr", "idents", "exprs", YY_NULLPTR
  };
#endif


#if XXSDEBUG
  const signed char
  parser::yyrline_[] =
  {
       0,    58,    58,    63,    64,    67,    68,    69,    70,    71,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    91,    92,    93,    96,    97,    98
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



void xxs::parser::error(const location_type& loc, const std::string& msg)
{
	throw xxs::syntax_error(loc);
}
