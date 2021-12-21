#include "token.h"

namespace RTree
{

    Token::Token(Type t, std::string l)
    {
        _type = t;
        _lexeme = l;

        if (_type == STRING)
            _raw = std::string("\"" + _lexeme + "\"");
    }

    Token::~Token(){}

    std::string Token::lexeme() const
    {
        return _lexeme;
    }

    std::string Token::raw() const
    {
        return _raw;
    }

    int Token::type() const
    {
        return _type;
    }

}