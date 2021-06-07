/* bison (GNU Bison) 3.7.4 */

%require "3.7"
%skeleton "lalr1.cc"
%language "c++"
%defines "parser.h"
%define api.token.constructor
%define api.value.type variant
%locations
%define api.prefix {xxs}

%parse-param {xxs::FunctionAst *& program}
/*
%lex-param {}
*/

%code requires {
	#include <memory>
	#include <format>
	#include "ast.hpp"
	#include "error.hpp"

	#define PARAMS std::vector<std::string>
	#define ASTS std::vector<PAST>
}

%code {
	#include <iostream>
	#include "ast.hpp"

	extern xxs::parser::symbol_type yylex();
}

%token FUNCTION "function" RETURN "return" IF "if" ELSE "else" NIL "nil"
%token INT "int" FLOAT "float" IDENT "identifier"
%token PLUS "+" MINUS "-" MUL "*" DIV "/"
%token LT "<" GT ">" EQ "=" EE "==" LTE "<=" GTE ">=" NE "!="
%token LPAREN "("  RPAREN ")" LBLOCK "{" RBLOCK "}" SEMICOLON ";" COMMA ","
%token ETEST ">>"

%right "="
%left "==" "!="
%left "<" ">" "<=" ">="
%left "+" "-"
%left "*" "/"
%left "("

%type <int> INT
%type <float> FLOAT
%type <std::string> IDENT
%type <PAST> expr stmt stmts
%type <PARAMS> idents
%type <ASTS> exprs

%start main
%%

main: stmts YYEOF {
	 program = new FunctionAst("__main", PARAMS(), $1);
}
;

stmts: stmt 			 { $$ = new BlockAst(); reinterpret_cast<BlockAst*>($$)->push($1); }
| stmts stmt 			 { $$ = $1; reinterpret_cast<BlockAst*>($$)->push($2); }
;

stmt: expr 			 ";"	{ $$ = $1; }
| expr 			 					{ $$ = $1; }
| IDENT "=" expr ";"  { $$ = new VarAssignAst($IDENT, token::EQ, $expr);}
| "return" expr  ";"  { $$ = new RetAst($expr); }
| "return" 			 ";"  { $$ = new RetAst(); }
;


expr: INT { $$ = new IntAst($1); }
| "nil" { $$ = new IntAst(NULL); }
| FLOAT { $$ = new FloatAst($1); }
| IDENT { $$ = new VarAccessAst($1); }
| "(" expr[e] ")" {$$ = $e;}
| "function" IDENT "(" idents[params] ")" "{" stmts "}" { $$ = new FunctionAst($IDENT, std::move($params), $stmts); }
| "function" IDENT "(" idents[params] ")" "{" "}" { $$ = new FunctionAst($IDENT, std::move($params), new BlockAst()); }
| "function" "(" idents[params] ")" "{" stmts "}" { $$ = new FunctionAst(std::move($params), $stmts); }
| "function" "(" idents[params] ")" "{" "}" { $$ = new FunctionAst(std::move($params), new BlockAst()); }
|	expr[name] "(" exprs[args] ")" { $$ = new CallAst($name, std::move($args)); }
| expr "+" expr {$$ = new BinaryAst(token::PLUS, $1, $3);}
| expr "-" expr {$$ = new BinaryAst(token::MINUS, $1, $3);}
| expr "*" expr {$$ = new BinaryAst(token::MUL, $1, $3);}
| expr "/" expr {$$ = new BinaryAst(token::DIV, $1, $3);}
;

idents: %empty { $$ = PARAMS(); }
|	IDENT { $$ = PARAMS{$1}; }
|	idents "," IDENT { $$ = std::move($1); $$.push_back($3); }
;

exprs:  %empty { $$ = ASTS(); } 
| expr { $$ = ASTS{$1}; }
|	exprs "," expr { $$ = std::move($1); $$.push_back($3); }
;

%%

void xxs::parser::error(const location_type& loc, const std::string& msg)
{
	throw xxs::syntax_error(loc);
}
