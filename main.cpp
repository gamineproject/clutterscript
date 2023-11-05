#include "src/cs.hpp"
#include <iostream>
#include <vector>
#include <string>

int main() {
    while (true) {
        std::string code;
        std::cout << "REPL> ";
        std::getline(std::cin, code);
        chconf::CH_COLOR = 1;
        if (code.empty()) {
            break; // Exit the REPL if no input is provided
        }
        cs::newContext("context1");
        cs::js::eval("context1", code);
        std::cout << std::endl;
        cs::deleteContext("context1");
    }
    return 0;
}
