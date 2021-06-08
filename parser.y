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

  #define M(o) std::move(o)
  #define BINARY(op) yylhs.value.as < xxs::ast_ptr > () = new BinaryAst(token::op,  yystack_[0].value.as < xxs::ast_ptr > (),  yystack_[2].value.as < xxs::ast_ptr > ())
  #define IPPMM(i, op) new VarAssignAst( yystack_[i].value.as<std::string>(), token::EQ, new BinaryAst(token::PLUS, new VarAccessAst(yystack_[i].value.as<std::string>()), new IntAst(1)) )
}

%code {
  #include <iostream>
  #include "ast.hpp"

  extern xxs::parser::symbol_type yylex();
}

%token FUNCTION "function" RETURN "return" IF "if" FOR "for" ELSE "else" NIL "nil" WHILE "while"
%token INT "int" FLOAT "float" IDENT "identifier"
%token PLUS "+" MINUS "-" MUL "*" DIV "/" PPLUS "++" MMINUS "--"
%token LT "<" GT ">" EQ "=" EE "==" LTE "<=" GTE ">=" NE "!="
%token LPAREN "("  RPAREN ")" LBLOCK "{" RBLOCK "}" SEMICOLON ";" COMMA ","
%token ETEST ">>"

%right "="
%left "==" "!="
%left "<" ">" "<=" ">="
%left "+" "-"
%left "*" "/"
%right "++" "--"
%left "("

%type <int> INT
%type <float> FLOAT
%type <std::string> IDENT func_begin
%type <xxs::ast_ptr> primary expr expr_1 stmt  for_begin for_cond for_step
%type <xxs::StmtsAst*> stmts else_1 block_1 block_2
%type <params_t> idents
%type <asts_t> exprs

%start main
%%

main: stmts YYEOF 																		      { _main = new FuncAst("__main", params_t(), $1);  }
;

stmts: stmt 			 																		      { $$ = new StmtsAst({$1}); 							          }
| 		stmts stmt 			 																      { $$ = $1; $$->push($2); 													}
;

/* 由于expr_1可选的分号,会造成冲突 */
stmt: expr_1 			        																  { $$ = $1; 																				}
|     expr_1           ";"                                  { $$ = $1; 																				}
| 		"return" expr_1  ";"  													      { $$ = new RetAst($2); 														}
| 		"return" 			   ";"    													    { $$ = new RetAst(); 															}
| 		"if" "(" expr_1 ")" block_2 else_1  								  { $$ = new IfAst($3, $block_2, $else_1); 				  }
| 		for_begin for_cond ";" for_step ")" block_2  	        { $$ = new ForAst($1, $2, $4, $block_2);          }
|     "while" "(" expr_1[cond] ")" block_2                  { $$ = new ForAst(nullptr, $cond, nullptr, $block_2);}
;

block_1:	"{" stmts "}"																      { $$ = $stmts;                                    }
| 				"{"       "}"																      { $$ = new StmtsAst();                            }
;

block_2:	block_1 																		      { $$ = $1; }
| 				stmt  							  											      { $$ = new StmtsAst({ $1 });                      }
;


for_begin: "for" "(" expr_1 ";" 										        { $$ = $expr_1;                                   }
|          "for" "("        ";" 										        { $$ = nullptr;                                   }
;

for_cond: expr_1    { $$ = $1; }
|         %empty    { $$ = nullptr; }
;

for_step: expr_1    { $$ = $1; }
|         %empty    { $$ = nullptr; }
;

else_1: %empty 																			        { $$ = new StmtsAst(); 														}
| 			"else" block_2  											  			      { $$ = $2; 																		    }
;

expr_1: IDENT "=" expr_1  													        { $$ = new VarAssignAst($1, token::EQ, $3);				}
|				expr 																				        { $$ = $1; 																				}
| 			func_begin "(" idents ")" block_1 									{ $$ = new FuncAst($1, M($idents), $block_1); 		}
;

func_begin: "function" IDENT 	  								            { $$ = $2; 																   			}
|						"function" 			 										            { $$ = ""; 																   			}
;

expr: primary 																			        { $$ = $1;                                        }
| 		"(" expr_1 ")" 																        { $$ = $2;                                        }
|			expr "(" exprs ")" 								                    { $$ = new CallAst($1, M($3));                    }
| 		expr "+" expr 																        { BINARY(PLUS);				                            }
| 		expr "-" expr 																        { BINARY(MINUS);			                          	}
| 		expr "*" expr 																        { BINARY(MUL);				                          	}
| 		expr "/" expr 																        { BINARY(DIV);				                          	}
| 		expr ">" expr 																        { BINARY(GT);					                            }
| 		expr "<" expr 																        { BINARY(LT);					                            }
| 		expr ">=" expr 																        { BINARY(GTE);				                          	}
| 		expr "<=" expr 																        { BINARY(LTE);				                          	}
| 		expr "==" expr 																        { BINARY(EE);					                            }
| 		expr "!=" expr 																        { BINARY(NE);					                            }
|     IDENT "++"                                            { $$ = new StmtsAst{{ new VarAccessAst($1), IPPMM(1, PLUS), }, false}; }
|     IDENT "--"  %prec "++"                                { $$ = new StmtsAst{{ new VarAccessAst($1), IPPMM(1, MINUS) }, false}; }
|     "++" IDENT                                            { $$ = IPPMM(0, PLUS);                            }
|     "--" IDENT  %prec "++"                                { $$ = IPPMM(0, MINUS);                           }
;

primary: INT 																					      { $$ = new IntAst($1);		  											}
| 			"nil" 																				      { $$ = new IntAst(NULL); 													}
| 			FLOAT 																				      { $$ = new FloatAst($1);		 											}
| 			IDENT 																				      { $$ = new VarAccessAst($1);                      }
;

idents: %empty 																				      { $$ = params_t(); 										  					}
|				IDENT 																				      { $$ = params_t{$1}; 															}
|       idents "," IDENT  														      { $$ = M($1); $$.push_back($3); 					        }
;

exprs:  %empty 																				      { $$ = asts_t(); 											  					}
| 			expr_1 																					    { $$ = asts_t{$1}; 																}
|				exprs "," expr_1 																    { $$ = M($1); $$.push_back($3); 					        }
;

%%

#undef M
#undef BINARY
#undef IPPMM

void xxs::parser::error(const location_type& loc, const std::string& msg)
{
  throw xxs::syntax_error(loc);
}
