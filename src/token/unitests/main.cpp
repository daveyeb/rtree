#include "../token.h"
#include <iostream>

using namespace RTToken;

int main(){
    Token imports(STRING, "Goat");

    std::cout << imports.lexeme() << std::endl;
    std::cout << imports.raw() << std::endl;
    std::cout << imports.type() << std::endl;

    std::cout << C_PAREN << std::endl;
    std::cout << F_SLASH << std::endl;
    std::cout << L_THAN << std::endl;
}