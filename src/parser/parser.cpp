#include "parser.h"
#include "token/token.h"

Parser::Parser(std::vector<Token> in)
{
    tokens = in;
    current = 0;
}

Parser::~Parser()
{
    tokens.clear();
}

Token Parser::getCurrent()
{
    Token token(UNKNOWN, "");
    size_t size = tokens.size();

    if (tokens.empty())
        return token;

    if (!(current < size))
        return token;

    return tokens[current];
}

Token Parser::next()
{
    Token token(UNKNOWN, "");
    size_t size = tokens.size();

    if (tokens.empty())
        return token;

    if (!((current + 1) < size))
        return token;

    return tokens[++current];
}

std::vector<Token> Parser::peek(size_t n)
{
    std::vector<Token> buffer;

    size_t size = tokens.size();
    size_t index = 0;
    size_t tmp = current;

    if ((current + n) >= size)
        return buffer;

    while (index < n)
    {
        buffer.push_back(tokens[++tmp]);
        index++;
    }

    return buffer;
}

std::set<std::string> Parser::scanDependencies(lang spec){
    std::set<std::string> importNames;

    int size = tokens.size();


    if(tokens.empty())
        return importNames;

    while(current < (size - 1)){
        spec(this, importNames);
    }
    
    return importNames;
}