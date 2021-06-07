#include <iostream>
#include <format>
#include "parser.h"
#include "CodeGen.hpp"

#define yyin xxsin
#define yyout xxsout
extern xxs::parser::symbol_type yylex();
extern FILE *yyin, *yyout;

int parserArgv(int argc, char *argv[]);

int main(int argc, char *argv[])
{
  if (parserArgv(argc, argv))
    return 1;

  try
  {
    xxs::FunctionAst *my_main;
    xxs::parser parser(my_main);
    parser.parse();

    if (my_main)
    {
      // printf("ast id %d\n", program->id());
      xxs::CodeGen cg;
      cg.init_main(my_main);
      cg.print();
      delete my_main;
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }

  return 0;
}

int parserArgv(int argc, char *argv[])
{
  if (argc > 1)
  {

    // xxscript.exe test.xxs
    if (argc == 2)
    {
      fopen_s(&yyin, argv[1], "r");
      return 0;
    }

    // xxscript.exe -i test.xxs
    char prefix;
    char *opt;
    int valIndex;
    char *val;
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
          if (valIndex < argc)
          {
            val = argv[valIndex];
            fopen_s(&yyin, val, "r");
          }
          else
          {
            std::cout << std::format("Error:'-{}'参数需要值", opt) << "\n";
            return 1;
          }
          break;
        case 'o':
          valIndex = ++i;
          if (valIndex < argc)
          {
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
