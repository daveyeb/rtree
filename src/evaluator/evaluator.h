#ifndef __RT__SPEC__H__
#define __RT__SPEC__H__

#include "common.h"

namespace RTree
{

    class Token;
    class Lexer;

    class Evaluator
    {
    public:
        Evaluator();
        virtual ~Evaluator();

        void identifier(Lexer *const l, std::vector<Token> &tokens) const;
        void comment(Lexer *const l) const;
        void literal(Lexer *const l, std::vector<Token> &tokens) const;
        void punctuation(Lexer *const l, std::vector<Token> &tokens) const;

    private:
        std::vector<std::string> ids;
        std::string pts;
    };

}

#endif