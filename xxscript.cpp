#include <iostream>
#include <format>
#include "parser.h"
#include "CodeGen.hpp"

#define yyin xxsin
#define yyout xxsout
extern xxs::parser::symbol_type yylex();
extern FILE *yyin, *yyout;

int parserArgv(int argc, char *argv[]);

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

extern "C" DLLEXPORT int print(int x)
{
  std::cout << std::format("{}", x) << std::endl;
  return 0;
}

bool bJit,    // jit执行代码
    bIr,  // 打印IR
    bPass,   // 开启优化
    bParser; // 测试parser

int main(int argc, char *argv[])
{
  if (parserArgv(argc, argv))
    return 1;

  try
  {
    xxs::FuncAst *my_main;
    xxs::parser parser(my_main);
    parser.parse();

    if (my_main)
    {
      if (!bParser)
      {
        xxs::CodeGen cg{bPass};
        cg.codegen(my_main);
        if (bIr)
          cg.print();
        if (bJit)
          cg.jit();
      }
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
    // xxscript.exe -i test.xxs
    char prefix;
    std::string_view opt;
    int valIndex;
    char *val;
    for (size_t i = 1; i < argc; i++)
    {
      prefix = *argv[i];
      if (prefix == '-')
      {
        opt = argv[i] + 1;
        if (opt == "jit")
        {
          bJit = true;
          continue;
        }

        if (opt == "ir")
        {
          bIr = true;
          continue;
        }

        if (opt == "pass")
        {
          bPass = true;
          continue;
        }

        if (opt == "parser")
        {
          bParser = true;
          continue;
        }

        switch (opt.at(0))
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
