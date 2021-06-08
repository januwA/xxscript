#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "llvm/IR/IRBuilder.h"

namespace xxs
{
    class Context
    {
    public:
        std::vector<std::map<std::string, llvm::AllocaInst *>> scopes;
        std::vector<std::map<std::string, llvm::Function *>> func_scopes;

        Context() {}

        void operator++()
        {
            // 会自动push一个map
            scopes.emplace_back();
            func_scopes.emplace_back();
        }

        void operator--()
        {
            scopes.pop_back();
            func_scopes.pop_back();
        }

        llvm::AllocaInst *get(std::string_view name)
        {
            // 倒序遍历scopes表，找变量
            for (auto m = scopes.crbegin(); m != scopes.crend(); ++m)
            {
                // 找到对应的name 则返回value
                if (auto p = m->find(name.data()); p != m->end())
                    return p->second;
            }

            // 没有找到返回0
            return nullptr;
        }

        void set(std::string_view name, llvm::AllocaInst *value)
        {
            // 向最后scope添加变量
            scopes.back().emplace(name, value);
        }

        void setf(std::string_view name, llvm::Function *func)
        {
            func_scopes.back().emplace(name, func);
        }

        llvm::Function *getf(std::string_view name)
        {
            for (auto m = func_scopes.crbegin(); m != func_scopes.crend(); ++m)
            {
                if (auto p = m->find(name.data()); p != m->end())
                    return p->second;
            }
            return nullptr;
        }
    };
};