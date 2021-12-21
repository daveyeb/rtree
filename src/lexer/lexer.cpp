#include "lexer.h"
#include "token/token.h"
#include "evaluator/evaluator.h"

namespace RTree
{

    Lexer::Lexer(const std::string b)
    {
        _buffer = b;
        _current = 0;
    }

    Lexer::~Lexer()
    {
    }

    char Lexer::current() const
    {
        size_t size = _buffer.length();
        if (!(size - 1))
            return -1;

        if (!(_current < size - 1))
            return -1;

        return _buffer[_current];
    }

    char Lexer::next()
    {
        size_t size = _buffer.length();
        if (!size)
            return -1;

        if (!((_current + 1) < size))
            return -1;

        return _buffer[++_current];
    }

    std::string Lexer::peek(size_t n) const
    {
        size_t size = _buffer.length();
        size_t tmp = _current;

        if ((_current + n) >= size)
            return std::string("");

        return _buffer.substr(++tmp, n);
    }

    std::vector<Token>& Lexer::scanTokens()
    {
        Evaluator eval;

        if (_buffer.empty())
            return tokens;

        // printf("Here Lexer 1\n");

        while (_current < (_buffer.length() - 1))
        {
            // printf("%d %lu\n", _current, (_buffer.length() - 1));

            eval.identifier(this, tokens);
            eval.comment(this);
            eval.punctuation(this, tokens);
            eval.literal(this, tokens);
        }

        // printf("Here Lexer 2\n");

        return tokens;
    }

}
