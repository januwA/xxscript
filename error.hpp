#pragma once

#include <iostream>
#include <format>
#include "location.hh"

namespace xxs
{
  struct base_error : public std::exception
  {
    using _Mybase = std::exception;

    std::string err(const location &loc, std::string_view msg)
    {
      return std::format("{}:{}:{} {}:{}", msg.data(), loc.begin.line, loc.begin.column, loc.end.line, loc.end.column);
    }

    base_error(const location &loc, std::string_view msg = "")
        : _Mybase(err(loc, msg).data())
    {
    }

    ~base_error() = default;
  };

  struct char_error : public base_error
  {
    using _Mybase = base_error;
    char_error(const location &loc)
        : _Mybase(loc, "Char Error")
    {
    }
  };

  struct syntax_error : public base_error
  {
    using _Mybase = base_error;
    syntax_error(const location &loc)
        : _Mybase(loc, "Syntax Error")
    {
    }
  };

  struct runtime_error : public base_error
  {
    using _Mybase = base_error;
    runtime_error(const location &loc)
        : _Mybase(loc, "Runtime Error")
    {
    }
  };
}