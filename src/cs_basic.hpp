#ifndef CS_BASIC_HPP
#define CS_BASIC_HPP
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <stack>
#include "cs_ch.hpp"

namespace cs
{
    namespace contextmgr
    {
        std::vector<std::string> contexts;
    }
    namespace data{
        std::vector<std::string> lets;
    }
    void newContext(const std::string &contextName)
    {
        if (std::find(cs::contextmgr::contexts.begin(), cs::contextmgr::contexts.end(), contextName) != cs::contextmgr::contexts.end())
        {
            ch::error("Error", "Context '" + contextName + "' already exists.", {"cs_basic", "cs_runtime"});
            std::cerr << "Error: Context '" << contextName << "' already exists." << std::endl;
            return;
        }
        cs::contextmgr::contexts.push_back(contextName);
    }

    void deleteContext(const std::string &contextName)
    {
        auto it = std::find(cs::contextmgr::contexts.begin(), cs::contextmgr::contexts.end(), contextName);
        if (it == cs::contextmgr::contexts.end())
        {
            ch::error("Error", "Context '" + contextName + "' doesn't exist.", {"cs_basic", "cs_runtime"});
            return;
        }
        cs::contextmgr::contexts.erase(it);
    }
    std::vector<std::string> lex(const std::string &code, const std::string &contextName)
    {
        std::vector<std::string> t1 = ch::jsonlex(code);
        std::vector<std::string> t2 = ch::memolex(t1, contextName);
        return t2;
    }

}
#endif