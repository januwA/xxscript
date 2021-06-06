/* win_flex.exe 2.6.4 */

%option noyywrap noline
%option prefix="xxs"

%{
#include <iostream>
#include "parser.h"

#define YY_DECL xxs::parser::symbol_type yylex()
xxs::location loc;
#define yyterminate() return xxs::parser::make_XXSEOF(loc)
#define _T(t) return xxs::parser::make_##t(loc)
#define _ST(t) return xxs::parser::make_##t(std::string(yytext, yyleng), loc)

#define YY_USER_ACTION loc.step(); loc.columns(yyleng);

%}

INT     [0-9]+
FLOAT   [0-9]*\.[0-9]+
IDENT   (?i:[a-z][a-z0-9]*)

%%

"+" { _T(PLUS); }
"-" { _T(MINUS); }
"*" { _T(MUL); }
"/" { _T(DIV); }

"<" { _T(LT); }
">" { _T(GT); }
"=" { _T(EQ); }
"==" { _T(EE); }
"<=" { _T(LTE); }
">=" { _T(GTE); }
"!=" { _T(NE); }
">>" { _T(ETEST); }

"(" { _T(LPAREN); }
")" { _T(RPAREN); }
"{" { _T(LBLOCK); }
"}" { _T(RBLOCK); }
";" { _T(SEMICOLON); }
"," { _T(COMMA); }


"nil" { _T(NIL); }
"function" { _T(FUNCTION); }
"return" { _T(RETURN); }
"if" { _T(IF); }
"else" { _T(ELSE); }

{INT} { _ST(INT); }
{FLOAT} { _ST(FLOAT); }
{IDENT} { _ST(IDENT); }


"//"[^\n]*\n { loc.lines(); }
[\n]  { loc.lines(); }
[ \t\r] { }

. { printf("char error.\n"); }

%%

