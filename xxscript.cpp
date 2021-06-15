#include <iostream>
#include <format>
#include <stdarg.h>

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

extern "C" DLLEXPORT std::string llval2str(int64_t llval)
{
  return "llvmval";
}

extern "C" DLLEXPORT int print(int64_t count, char *_format, ...)
{
  // printf("count:%d\n", count);
  // printf("format:%s\n", _format);

  va_list vl;
  va_start(vl, _format);
  char *c1, *c2, *c3, *c4, *c5, *c6, *c7, *c8, *c9, *c10;
  switch (count)
  {
  case 0:
    std::cout << std::format(_format) << std::endl;
    break;
  case 1:
    std::cout << std::format(_format, va_arg(vl, char *)) << std::endl;
    break;
  case 2:
    c1 = va_arg(vl, char *);
    c2 = va_arg(vl, char *);
    std::cout << std::format(_format, c1, c2) << std::endl;
    break;
  case 3:
    c1 = va_arg(vl, char *);
    c2 = va_arg(vl, char *);
    c3 = va_arg(vl, char *);
    std::cout << std::format(_format, c1, c2, c3) << std::endl;
    break;
  case 4:
    c1 = va_arg(vl, char *);
    c2 = va_arg(vl, char *);
    c3 = va_arg(vl, char *);
    c4 = va_arg(vl, char *);
    std::cout << std::format(_format, c1, c2, c3, c4) << std::endl;
    break;
  case 5:
    c1 = va_arg(vl, char *);
    c2 = va_arg(vl, char *);
    c3 = va_arg(vl, char *);
    c4 = va_arg(vl, char *);
    c5 = va_arg(vl, char *);
    std::cout << std::format(_format, c1, c2, c3, c4, c5) << std::endl;
    break;
  case 6:
    c1 = va_arg(vl, char *);
    c2 = va_arg(vl, char *);
    c3 = va_arg(vl, char *);
    c4 = va_arg(vl, char *);
    c5 = va_arg(vl, char *);
    c6 = va_arg(vl, char *);
    std::cout << std::format(_format, c1, c2, c3, c4, c5, c6) << std::endl;
    break;
  case 7:
    c1 = va_arg(vl, char *);
    c2 = va_arg(vl, char *);
    c3 = va_arg(vl, char *);
    c4 = va_arg(vl, char *);
    c5 = va_arg(vl, char *);
    c6 = va_arg(vl, char *);
    c7 = va_arg(vl, char *);
    std::cout << std::format(_format, c1, c2, c3, c4, c5, c6, c7) << std::endl;
    break;
  case 8:
    c1 = va_arg(vl, char *);
    c2 = va_arg(vl, char *);
    c3 = va_arg(vl, char *);
    c4 = va_arg(vl, char *);
    c5 = va_arg(vl, char *);
    c6 = va_arg(vl, char *);
    c7 = va_arg(vl, char *);
    c8 = va_arg(vl, char *);
    std::cout << std::format(_format, c1, c2, c3, c4, c5, c6, c7, c8) << std::endl;
    break;
  case 9:
    c1 = va_arg(vl, char *);
    c2 = va_arg(vl, char *);
    c3 = va_arg(vl, char *);
    c4 = va_arg(vl, char *);
    c5 = va_arg(vl, char *);
    c6 = va_arg(vl, char *);
    c7 = va_arg(vl, char *);
    c8 = va_arg(vl, char *);
    c9 = va_arg(vl, char *);
    std::cout << std::format(_format, c1, c2, c3, c4, c5, c6, c7, c8, c9) << std::endl;
    break;
  case 10:
    c1 = va_arg(vl, char *);
    c2 = va_arg(vl, char *);
    c3 = va_arg(vl, char *);
    c4 = va_arg(vl, char *);
    c5 = va_arg(vl, char *);
    c6 = va_arg(vl, char *);
    c7 = va_arg(vl, char *);
    c8 = va_arg(vl, char *);
    c9 = va_arg(vl, char *);
    c10 = va_arg(vl, char *);
    std::cout << std::format(_format, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10) << std::endl;
    break;
  default:
    break;
  }

  va_end(vl);
  return 0;
}

bool bJit,   // jit执行代码
    bIr,     // 打印IR
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
