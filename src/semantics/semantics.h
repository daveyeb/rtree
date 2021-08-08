#ifndef __RT__SEMANTICS__H__
#define __RT__SEMANTICS__H__

#include "common.h"

class Token;
class Lexer; 

void identifier(Lexer *const l, std::vector<Token> &tokens);
void comment(Lexer *const l);
void literal(Lexer *const l, std::vector<Token> &tokens);
void punctuation(Lexer *const l, std::vector<Token> &tokens);

#endif