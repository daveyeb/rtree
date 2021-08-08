#ifndef __RT__TOKEN__H__
#define __RT__TOKEN__H__

#include "common.h"

enum Type
{
    UNKNOWN,
    // keywords
    FROM,
    IMPORT,
    USE,
    LOAD,
    REQUIRE,
    INCLUDE,
    // punctuations
    SYMBOL,
    O_PAREN = 40,
    C_PAREN = 41,
    D_QUOTE = 34,
    S_QUOTE = 39,
    POUND = 35,
    ASTERISK = 42,
    COMMA = 44,
    PERIOD = 46,
    F_SLASH = 47,
    S_COLON = 59,
    L_THAN = 60,
    G_THAN = 62,
    // literals
    LITERAL,
    STRING,
    RT_EOF
};

class Token
{
private:
    Type type;
    std::string lexeme;
    std::string raw;

public:
    Token(Type t, std::string l, std::string r = "");
    ~Token();

    std::string getLexeme();
    Type getType();
};

#endif