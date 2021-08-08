#ifndef __RT__LEXER_H__
#define __RT__LEXER_H__

#include "common.h"
#include "scanner/scanner.h"

class Token; 

class Lexer : public Scanner<char>
{
private:
    std::string buffer;

public:
    Lexer(const std::string in);
    ~Lexer();

    char getCurrent();
    char next();

    std::vector<Token> scanTokens();
    std::string peek(size_t n);
};





#endif