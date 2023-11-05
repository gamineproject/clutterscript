#ifndef CS_RUNTIME_HPP
#define CS_RUNTIME_HPP

#include <vector>
#include <string>
#include "cs_basic.hpp" // Assuming cs_basic.hpp contains the ch::error function

namespace cs
{
    namespace js
    {
        void declareValue(const std::string &val, std::vector<std::string>::iterator &it, const std::vector<std::string> &JS)
        {
            auto li = it;
            if (*it == val)
            {
                ++li; // Move the iterator to the next token
                // Check if there is another token
                if (it != JS.end())
                {
                    std::string name = *li;

                    ++li; // Move the iterator to the next token
                    // Check if there is an assignment operator
                    if (li != JS.end() && *li == "=")
                    {
                        ++li; // Move the iterator to the next token
                        // Check if there is a value token
                        if (li != JS.end())
                        {
                            std::string value = *li;

                            // Store the variable name and value in the vars vector
                            if (value == "\"\"")
                            {
                                ch::error("SyntaxError", "Unexpected token.", {"cs_basic", "cs_runtime"});
                            }
                            else
                            {
                                values.push_back(val + "##" + name + "##" + value);
                            }
                        }
                        else
                        {
                            ch::error("SyntaxError", "Missing value in assignment.", {"cs_basic", "cs_runtime"});
                        }
                    }
                    else
                    {
                        ch::error("SyntaxError", "Missing assignment operator in variable declaration.", {"cs_basic", "cs_runtime"});
                    }
                }
                else
                {
                    ch::error("SyntaxError", "idk", {"cs_runtime"});
                }
            }
        }

        std::vector<std::string> eval(const std::string &contextName, const std::string &code)
        {
            std::vector<std::string> JS = cs::lex(code, contextName);

            // Create iterators to iterate over the tokens
            auto it = JS.begin();
            auto end = JS.end();

            // Iterate over the tokens in the JS vector
            while (it != end)
            {
                declareValue("let", it, end);
                declareValue("var", it, end);
                if (it != end)
                {
                    ch::error("SyntaxError", "Unexpected token.", {"cs_runtime"});
                    break;
                }
            }

            return {""};
        }
    }
}

#endif // CS_RUNTIME_HPP
