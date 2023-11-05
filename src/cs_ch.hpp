#ifndef CS_CH_HPP
#define CS_CH_HPP
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <stack>
namespace chconf
{
    int CH_ERROR_MADE = 0;
    int CH_COLOR = 0;
}
namespace ch
{
    void error(const std::string &type, const std::string &msg, const std::vector<std::string> &locs)
    {
        std::vector<std::string> locats;
        for (std::string lt : locs)
        {
            locats.push_back(lt);
        }
        locats.push_back("cs");
        if (!msg.empty())
        {
            if (!chconf::CH_COLOR)
            {
                std::cerr << type << ": " << msg << std::endl;
            }
            else
            {
                std::cerr << "\u001b[31;1m" << type << "\u001b[0m: " << msg << std::endl;
            }
            for (const std::string &loc : locats)
            {
                std::cout << "    at " << loc << std::endl;
            }
        }
        chconf::CH_ERROR_MADE = 1;
    }

    std::vector<std::string> memolex(std::vector<std::string> code, const std::string &contextName)
{
    static std::unordered_map<std::string, std::vector<std::string>> memo;

    std::vector<std::string> tokens;

    std::string currentToken;

    std::stack<char> parentheses;

    for (char c : code)
    {
        if (isalpha(c))
        {
            currentToken += c;
        }
        else if (c == ' ')
        {
            if (!currentToken.empty())
            {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
        }
        else if (c == '(')
        {
            parentheses.push(c);
        }
        else if (c == ')')
        {
            if (parentheses.empty())
            {
                ch::error("Error", "Unbalanced parentheses.", {"cs_basic", "cs_runtime"});
                return tokens;
            }
            parentheses.pop();
        }
        else
        {
            if (memo.find(currentToken) != memo.end())
            {
                tokens.push_back(memo[currentToken]);
                currentToken.clear();
            }
            else
            {
                if (c == '"' || c == '\'' || c == '`')
                {
                    tokens.push_back(std::string(1, c));
                }
                else
                {
                    tokens.push_back(currentToken);
                    currentToken.clear();
                }
            }
        }
    }

    if (!currentToken.empty())
    {
        tokens.push_back(currentToken);
    }

    if (!chconf::CH_ERROR_MADE)
    {
        return tokens;
    }
    else
    {
        return {""};
    }
}

    std::vector<std::string> jsonlex(const std::string &code)
    {
        std::vector<std::string> tokens;
        std::string currentToken;
        bool inString = false;
        char stringQuote;
        bool colonExpected = false;

        for (char c : code)
        {
            if (c == '"' || c == '\'' || c == '`')
            {
                if (!inString)
                {
                    inString = true;
                    stringQuote = c;
                    currentToken += c;
                }
                else if (inString && stringQuote == c)
                {
                    inString = false;
                    currentToken += c;
                    tokens.push_back(currentToken);
                    currentToken.clear();
                }
                else
                {
                    currentToken += c;
                }
            }
            else if (inString)
            {
                currentToken += c;
            }
            else if (c == '{' || c == '}' || c == '[' || c == ']' || c == ':' || c == ';')
            {
                if (!currentToken.empty())
                {
                    tokens.push_back(currentToken);
                    currentToken.clear();
                }
                tokens.push_back(std::string(1, c));

                if (c == '{' || c == '[')
                {
                    colonExpected = true;
                }
                else if (c == '}' || c == ']')
                {
                    colonExpected = false;
                }
            }
            else if (c == ' ')
            {
                if (!currentToken.empty())
                {
                    tokens.push_back(currentToken);
                    currentToken.clear();
                }
            }
            else
            {
                currentToken += c;
            }
        }

        if (!currentToken.empty())
        {
            tokens.push_back(currentToken);
        }

        if (tokens.empty())
        {
            ch::error("SyntaxError", "Unexpected end of input", {"lexer", "cs_basic"});
        }
        else if (tokens.front() == "{" && tokens.back() != "}")
        {
            ch::error("SyntaxError", "Missing closing brace '}'", {"lexer", "cs_basic"});
        }
        else if (tokens.front() == "[" && tokens.back() != "]")
        {
            ch::error("SyntaxError", "Missing closing bracket ']'", {"lexer", "cs_basic"});
        }
        else if (colonExpected)
        {
            ch::error("SyntaxError", "Colon expected", {"lexer", "cs_basic"});
        }

        if (!chconf::CH_ERROR_MADE)
        {
            return tokens;
        }
        else
        {
            return {""};
        }
    }

}
#endif