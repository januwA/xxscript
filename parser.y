/* bison (GNU Bison) 3.7.4 */

%require "3.7"
%skeleton "lalr1.cc"
%language "c++"
%defines "parser.h"
%define api.token.constructor
%define api.value.type variant
%locations
%define api.prefix {xxs}

%parse-param {xxs::FuncAst *& _main}
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

%token FUNCTION "function" RETURN "return" IF "if" FOR "for" ELSE "else" NIL "nil"
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
%type <xxs::ast_ptr> primary expr expr_1 stmt  for_begin
%type <xxs::StmtsAst*> stmts else_1 block_1 block_2
%type <params_t> idents
%type <asts_t> exprs

%start main
%%

main: stmts YYEOF 																		      { _main = new FuncAst("__main", params_t(), $1);  }
;

stmts: stmt 			 																		      { $$ = new StmtsAst(); $$->push($1); 							}
| 		stmts stmt 			 																      { $$ = $1; $$->push($2); 													}
;

stmt: expr_1 			 ";"																      { $$ = $1; 																				}
| 		expr_1 			 																		      { $$ = $1; 																				}
| 		"return" expr_1  ";"  													      { $$ = new RetAst($2); 														}
| 		"return" 			 ";"    													      { $$ = new RetAst(); 															}
| 		"if" "(" expr_1 ")" block_2 else_1  								  { $$ = new IfAst($3, $block_2, $else_1); 				  }
| 		for_begin expr_1[cond] ";" expr_1[step] ")" block_2  	{ $$ = new ForAst($1, $cond, $step,   $block_2);  }
;

block_1:	"{" stmts "}"																      { $$ = $stmts; 									                 }
| 				"{"       "}"																      { $$ = new StmtsAst(); 					                 }
;

block_2:	block_1 																		      { $$ = $1; }
| 				stmt  							  											      { $$ = new StmtsAst({ $1 });                      }
;

for_begin: "for" "(" expr_1 ";" 										        { $$ = $expr_1;                                   }
;

else_1: %empty 																			        { $$ = new StmtsAst(); 														}
| 			"else" block_2  											  			      { $$ = $2; 																		    }
;

expr_1:  IDENT "=" expr_1  													        { $$ = new VarAssignAst($1, token::EQ, $3);				}
|				expr 																				        { $$ = $1; 																				}
| 			func_begin "(" idents ")" block_1 									{ $$ = new FuncAst($1, std::move($idents), $block_1); 				}
;

func_begin: "function" IDENT 	  								            { $$ = $2; 																   			}
|						"function" 			 										            { $$ = ""; 																   			}
;

expr: primary 																			        { $$ = $primary;																	}
| 		"(" expr_1 ")" 																        { $$ = $expr_1; 																	}
|			expr[name] "(" exprs[args] ")" 								        { $$ = new CallAst($name, std::move($args)); 			}
| 		expr "+" expr 																        { $$ = new BinaryAst(token::PLUS, $1, $3);				}
| 		expr "-" expr 																        { $$ = new BinaryAst(token::MINUS, $1, $3);				}
| 		expr "*" expr 																        { $$ = new BinaryAst(token::MUL, $1, $3);					}
| 		expr "/" expr 																        { $$ = new BinaryAst(token::DIV, $1, $3);					}
| 		expr ">" expr 																        { $$ = new BinaryAst(token::GT, $1, $3);					}
| 		expr "<" expr 																        { $$ = new BinaryAst(token::LT, $1, $3);					}
| 		expr ">=" expr 																        { $$ = new BinaryAst(token::GTE, $1, $3);					}
| 		expr "<=" expr 																        { $$ = new BinaryAst(token::LTE, $1, $3);					}
| 		expr "==" expr 																        { $$ = new BinaryAst(token::EE, $1, $3);					}
| 		expr "!=" expr 																        { $$ = new BinaryAst(token::NE, $1, $3);					}
;

primary: INT 																					      { $$ = new IntAst($1);		  											}
| 			"nil" 																				      { $$ = new IntAst(NULL); 													}		
| 			FLOAT 																				      { $$ = new FloatAst($1);		 											}
| 			IDENT 																				      { $$ = new VarAccessAst($1);											}
;

idents: %empty 																				      { $$ = params_t(); 										  					}
|				IDENT 																				      { $$ = params_t{$1}; 															}
|				idents "," IDENT  														      { $$ = std::move($1); $$.push_back($3); 					}
;

exprs:  %empty 																				      { $$ = asts_t(); 											  					} 
| 			expr_1 																					    { $$ = asts_t{$1}; 																}
|				exprs "," expr_1 																    { $$ = std::move($1); $$.push_back($3); 					}
;

%%

void xxs::parser::error(const location_type& loc, const std::string& msg)
{
  throw xxs::syntax_error(loc);
}
