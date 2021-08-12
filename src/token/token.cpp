#include "token.h"

Token::Token(Type t, std::string l, std::string r)
{
    type = t;
    lexeme = l;
    raw = r;
}

Token::~Token() {}

std::string Token::getLexeme()
{
    return lexeme;
}

Type Token::getType()
{
    return type;
}
