#ifndef __RT__SEMANTICS__H__
#define __RT__SEMANTICS__H__

#include "common.h"

class Token;
class Lexer;

class Semantics
{
public:
    static void identifier(Lexer *const l, std::vector<Token> &tokens);
    static void comment(Lexer *const l);
    static void literal(Lexer *const l, std::vector<Token> &tokens);
    static void punctuation(Lexer *const l, std::vector<Token> &tokens);
};

#endif