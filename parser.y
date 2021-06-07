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

	typedef  std::vector<xxs::ast_ptr> asts_t;
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
%type <std::string> IDENT func_begin
%type <xxs::ast_ptr> primary expr expr_1 stmt 
%type <xxs::StmtsAst*> stmts then_1 else_1 func_end
%type <params_t> idents
%type <asts_t> exprs

%start main
%%

main: stmts YYEOF {  program = new FunctionAst("__main", params_t(), $1); }
;

stmts: stmt 			 		{ $$ = new StmtsAst(); $$->push($1); }
| 		stmts stmt 			 { $$ = $1; $$->push($2); }
;

stmt: expr_1 			 ";"									{ $$ = $1; }
| 		expr_1 			 											{ $$ = $1; }
| 		IDENT "=" expr_1 ";"  						{ $$ = new VarAssignAst($IDENT, token::EQ, $3);}
| 		"return" expr_1  ";"  						{ $$ = new RetAst($2); }
| 		"return" 			 ";"    						{ $$ = new RetAst(); }
| 		"if" "(" expr ")" then_1 else_1  	{ $$ = new IfAst($expr, $then_1, $else_1); }
;

then_1: "{" stmts "}"	  { $$ = $2; 						   }
| 			"{" 			"}"   { $$ = new StmtsAst();   }
|				stmt						{	$$ = new StmtsAst({$stmt}); }
;

else_1: %empty 									{ $$ = new StmtsAst(); 				}
| 			"else" "{" stmts "}"  	{ $$ = $stmts; 								}
| 			"else" "{"  		 "}"  	{ $$ = new StmtsAst();  			}
|				"else" stmt  						{ $$ = new StmtsAst({$stmt}); }
;

expr_1: expr 														{ $$ = $1; 																		 }
| 			func_begin idents func_end 			{ $$ = new FunctionAst($1, std::move($2), $3); }
;

func_begin: "function" IDENT "("	  { $$ = $2; 						}
|						"function" 			 "("		{ $$ = ""; 						}
;

func_end: ")" "{" stmts "}"						{ $$ = $stmts; 				 }
| 				")" "{" 			"}"						{ $$ = new StmtsAst(); }
;

expr: primary 													{ $$ = $primary;															}
| 		"(" expr_1 ")" 										{ $$ = $expr_1; 															}
|			expr[name] "(" exprs[args] ")" 		{ $$ = new CallAst($name, std::move($args)); 	}
| 		expr "+" expr 										{ $$ = new BinaryAst(token::PLUS, $1, $3);		}
| 		expr "-" expr 										{ $$ = new BinaryAst(token::MINUS, $1, $3);		}
| 		expr "*" expr 										{ $$ = new BinaryAst(token::MUL, $1, $3);			}
| 		expr "/" expr 										{ $$ = new BinaryAst(token::DIV, $1, $3);			}
| 		expr ">" expr 										{ $$ = new BinaryAst(token::GT, $1, $3);			}
| 		expr "<" expr 										{ $$ = new BinaryAst(token::LT, $1, $3);			}
| 		expr ">=" expr 										{ $$ = new BinaryAst(token::GTE, $1, $3);			}
| 		expr "<=" expr 										{ $$ = new BinaryAst(token::LTE, $1, $3);			}
| 		expr "==" expr 										{ $$ = new BinaryAst(token::EE, $1, $3);			}
| 		expr "!=" expr 										{ $$ = new BinaryAst(token::NE, $1, $3);			}
;

primary: INT 					{ $$ = new IntAst($1);		  	}
| 			"nil" 				{ $$ = new IntAst(NULL); 			}		
| 			FLOAT 				{ $$ = new FloatAst($1);		 	}
| 			IDENT 				{ $$ = new VarAccessAst($1);	}
;

idents: %empty 						{ $$ = params_t(); 										  }
|				IDENT 						{ $$ = params_t{$1}; 										}
|				idents "," IDENT  { $$ = std::move($1); $$.push_back($3); }
;

exprs:  %empty 					{ $$ = asts_t(); 											  } 
| 			expr 						{ $$ = asts_t{$1}; 											}
|				exprs "," expr 	{ $$ = std::move($1); $$.push_back($3); }
;

%%

void xxs::parser::error(const location_type& loc, const std::string& msg)
{
	throw xxs::syntax_error(loc);
}
