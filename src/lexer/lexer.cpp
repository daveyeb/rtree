#include "lexer.h"
#include "token.h"
#include "semantics.h"

Lexer::Lexer(const std::string in)
{
    buffer = in;
    current = 0;
}

Lexer::~Lexer()
{
}

char Lexer::getCurrent()
{
    size_t size = buffer.length();
    if (!(size - 1))
        return -1;

    if (!(current < size - 1))
        return -1;

    return buffer[current];
}

char Lexer::next()
{
    size_t size = buffer.length();
    if (!size)
        return -1;

    if (!((current + 1) < size))
        return -1;

    return buffer[++current];
}

std::string Lexer::peek(size_t n)
{
    size_t size = buffer.length();
    size_t tmp = current;

    if ((current + n) >= size)
        return std::string("");

    return buffer.substr(++tmp, n).c_str();
}

std::vector<Token> Lexer::scanTokens()
{
    std::vector<Token> tokens;

    if (buffer.empty())
        return tokens;

    while (current < (buffer.length() - 1))
    {
        identifier(this, tokens);
        comment(this);
        punctuation(this, tokens);
        literal(this, tokens);
    }

    return tokens;
}