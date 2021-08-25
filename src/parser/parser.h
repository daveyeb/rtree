#ifndef __RT__PARSER__H__
#define __RT__PARSER__H__

#include "common.h"
#include "scanner/scanner.h"

class Token;

class Parser : public Scanner<Token>
{
private:
    std::vector<Token> tokens;

public:
    Parser(std::vector<Token> t);
    ~Parser();

    Token getCurrent();
    Token next();

    size_t curr(){ return current; }

    std::vector<Token> peek(size_t n);
    std::set<std::string> scanDependencies(lang spec);
};



#endif