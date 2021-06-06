/* bison (GNU Bison) 3.7.4 */

%require "3.7"
%skeleton "lalr1.cc"
%language "c++"
%defines "parser.h"
%define api.token.constructor
%define api.value.type variant
%locations
%define api.prefix {xxs}

%parse-param {PAST& program}
/*
%lex-param {}
*/

%code requires {
	#include <memory>
	#include <format>
	#include "ast.h"
	#define PARAMS std::vector<std::string>
	#define ASTS std::vector<PAST>
}

%code {
	#include <iostream>
	#include "ast.h"
	extern xxs::parser::symbol_type yylex();
}

%token FUNCTION "function" RETURN "return" IF "if" ELSE "else" NIL "nil"
%token INT "int" FLOAT "float" IDENT "identifier"
%token PLUS "+" MINUS "-" MUL "*" DIV "/"
%token LT "<" GT ">" EQ "=" EE "==" LTE "<=" GTE ">=" NE "!="
%token LPAREN "("  RPAREN ")" LBLOCK "{" RBLOCK "}" SEMICOLON ";" COMMA ","
%token ETEST ">>"

%left "="
%left "+" "-"
%left "*" "/"
%left "("

%type <std::string> INT FLOAT IDENT
%type <PAST> expr stmt stmts main
%type <PARAMS> idents
%type <ASTS> exprs

%start main
%%

main: stmts YYEOF {
 $$ = new FunctionAst("__main", PARAMS(), $1);
 program = $$;
}
;

stmts: stmt { $$ = new BlockAst(); reinterpret_cast<BlockAst*>($$)->push($1); }
| stmts stmt { $$ = $1; reinterpret_cast<BlockAst*>($$)->push($2); }
;

stmt: expr ";" { $$ = $1; }
| IDENT "=" expr ";" {$$ = new VarAssignAst($1, token::EQ, $3);}
| "return" expr ";" { $$=new RetAst($2); }
| "return" ";" { $$=new RetAst(); }
| ";" { }
;


expr: INT { $$ = new IntAst($1); }
| FLOAT { $$ = new FloatAst($1); }
| IDENT { $$ = new VarAccessAst($1); }
| "(" expr ")" {$$ = $2;}
| "function" IDENT "(" idents ")" "{" stmts "}" { $$ = new FunctionAst($2, M($4), $7); }
| "function" IDENT "(" idents ")" "{" "}" { $$ = new FunctionAst($2, M($4), new BlockAst()); }
| "function" "(" idents ")" "{" stmts "}" { $$ = new FunctionAst(M($3), $6); }
| "function" "(" idents ")" "{" "}" { $$ = new FunctionAst(M($3), new BlockAst()); }
|	expr "(" exprs ")" { $$ = new CallAst($1, M($3)); }
| expr "+" expr {$$ = new BinaryAst(token::PLUS, $1, $3);}
| expr "-" expr {$$ = new BinaryAst(token::MINUS, $1, $3);}
| expr "*" expr {$$ = new BinaryAst(token::MUL, $1, $3);}
| expr "/" expr {$$ = new BinaryAst(token::DIV, $1, $3);}
;

idents: %empty { $$ = PARAMS(); }
|	IDENT { $$ = PARAMS{$1}; }
|	idents "," IDENT { $$ = M($1); $$.push_back($3); }
;

exprs:  %empty { $$ = ASTS(); } 
| expr { $$ = ASTS{$1}; }
|	exprs "," expr { $$ = M($1); $$.push_back($3); }
;

%%

void xxs::parser::error(const location_type& loc, const std::string& msg)
{
	std::cout << std::format("{} {}:{} {}:{}", msg, loc.begin.line, loc.begin.column, loc.end.line, loc.end.column) << "\n";
}
