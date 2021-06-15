/* win_flex.exe 2.6.4 */

%option noyywrap noline
%option prefix="xxs"

%{
#include <iostream>
#include "parser.h"

xxs::location loc;
std::string str_buf;

#define YY_DECL xxs::parser::symbol_type yylex()
#define yyterminate() return xxs::parser::make_XXSEOF(loc)
#define _T(t)  return xxs::parser::make_##t(loc)
#define _IT(t) return xxs::parser::make_##t(std::stoll(yytext), loc)
#define _FT(t) return xxs::parser::make_##t(std::stod(yytext), loc)
#define _ST(t) return xxs::parser::make_##t(std::string(yytext, yyleng), loc)
#define _STR   return xxs::parser::make_STRING(str_buf, loc)

#define YY_USER_ACTION loc.step(); loc.columns(yyleng);
%}

INT     [0-9]+
FLOAT   [0-9]*\.[0-9]+
IDENT   (?i:[a-z][a-z0-9]*)

%x cmmt mcmmt mstr
%%

"+"             { _T(PLUS);         }
"-"             { _T(MINUS);        }
"*"             { _T(MUL);          }
"/"             { _T(DIV);          }
"%"             { _T(PERCENT);      }
"++"            { _T(PPLUS);        }
"--"            { _T(MMINUS);       }

"<"             { _T(LT);           }
">"             { _T(GT);           }
"="             { _T(EQ);           }
"=="            { _T(EE);           }
"<="            { _T(LTE);          }
">="            { _T(GTE);          }
"!="            { _T(NE);           }

"("             { _T(LPAREN);       }
")"             { _T(RPAREN);       }
"{"             { _T(LBLOCK);       }
"}"             { _T(RBLOCK);       }
"["             { _T(LSQUARE);      }
"]"             { _T(RSQUARE);      }
";"             { _T(SEMICOLON);    }
","             { _T(COMMA);        }
"?"             { _T(QUESTION);     }
":"             { _T(COLON);        }


"null"          { _T(NIL);          }
"true"          { _T(TTRUE);        }
"false"         { _T(TFALSE);       }
"function"      { _T(FUNCTION);     }
"return"        { _T(RETURN);       }
"if"            { _T(IF);           }
"else"          { _T(ELSE);         }
"for"           { _T(FOR);          }
"while"         { _T(WHILE);        }
"continue"      { _T(CONTINUE);     }
"break"         { _T(BREAK);        }

{INT}           { _IT(INT);         }
{FLOAT}         { _FT(FLOAT);       }
{IDENT}         { _ST(IDENT);       }


"//"            { BEGIN(cmmt);           }
<cmmt>.*        {                        }
<cmmt>\n        { loc.lines(); BEGIN(0); }

"/*"                   { BEGIN(mcmmt);     }
<mcmmt>[^*\n]*         {                   }
<mcmmt>"*"+[^*\n/]*    {                   }
<mcmmt>\n              { loc.lines();      }
<mcmmt>"*"+"/"         { BEGIN(0);         }

`               { str_buf=""; BEGIN(mstr);     }
<mstr>`         { BEGIN(0); _STR;              }
%{ /* 匹配字符串内的转义字符 */ %}
<mstr>\\n       { str_buf.push_back('\n');     }
<mstr>\\t       { str_buf.push_back('\t');     }
<mstr>\\r       { str_buf.push_back('\r');     }
<mstr>\\b       { str_buf.push_back('\b');     }
%{ /* 其它不认识的转义直接输出字符 */ %}
<mstr>\\(.|\n)  { str_buf.push_back(yytext[1]);}
%{ /* 其它字符 */ %}
<mstr>[^`\\\n]+ { str_buf += yytext;            }
<mstr>\n        { str_buf.push_back('\n');loc.lines();}


\n              { loc.lines();      }
[ \t\r]         {                   }

.               { printf("char error.\n"); }

%%

