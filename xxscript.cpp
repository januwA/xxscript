#include <iostream>
#include <format>
#include "parser.h"
#include "CodeGen.h"

#define yyin xxsin
#define yyout xxsout
extern xxs::parser::symbol_type yylex();
extern FILE* yyin, * yyout;

int parserArgv(int argc, char* argv[])
{
  if (argc > 1) {
    char prefix;
    char* opt;
    int valIndex;
    char* val;
    for (size_t i = 1; i < argc; i++)
    {
      prefix = *argv[i];
      if (prefix == '-')
      {
        opt = (argv[i] + 1);
        switch (*opt)
        {
        case 'i':
          valIndex = ++i;
          if (valIndex < argc) {
            val = argv[valIndex];
            fopen_s(&yyin, val, "r");
          }
          else {
            std::cout << std::format("Error:'-{}'参数需要值", opt) << "\n";
            return 1;
          }
          break;
        case 'o':
          valIndex = ++i;
          if (valIndex < argc) {
            val = argv[valIndex];
            std::cout << val << "\n";
          }
          break;
        default:
          std::cout << std::format("Error:未知的选项 '{}'", argv[i]) << "\n";
          return 1;
        }
      }
      else
      {
        std::cout << std::format("Error:未知的前缀 '{}'", prefix) << "\n";
        return 1;
      }
    }
    return 0;
  }
  return 0;
}

int main(int argc, char* argv[])
{
  if (parserArgv(argc, argv)) {
    return 1;
  }

  xxs::Ast* my_main;
  xxs::parser parser(my_main);
  parser.parse();
  if (my_main)
  {
    // printf("ast id %d\n", program->id());
    try
    {
      xxs::CodeGen cg{ reinterpret_cast<xxs::FunctionAst*>(my_main) };
      cg.print();
    }
    catch (const std::exception& e)
    {
      std::cout << e.what() << std::endl;
    }
    delete my_main;
  }
  return 0;
}
