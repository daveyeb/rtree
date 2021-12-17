#include "parser.h"
#include "token/token.h"
#include "languages/JavaScript.h"

namespace RTToken
{

    Parser::Parser(std::vector<Token> t)
    {
        _tokens = t;
        _current = 0;
    }

    Parser::~Parser()
    {
        _tokens.clear();
    }

    Token Parser::current() const
    {
        Token token(UNKNOWN, "");
        size_t size = _tokens.size();

        if (_tokens.empty())
            return token;

        if (!(_current < size))
            return token;

        return _tokens[_current];
    }

    Token Parser::next()
    {
        Token token(UNKNOWN, "");
        size_t size = _tokens.size();

        if (_tokens.empty())
            return token;

        if (!((_current + 1) < size))
            return token;

        return _tokens[++_current];
    }

    std::vector<Token> Parser::peek(size_t n) const
    {
        std::vector<Token> buffer;

        size_t size = _tokens.size();
        size_t index = 0;
        size_t tmp = _current;

        if ((_current + n) >= size)
            return buffer;

        while (index < n)
        {
            buffer.push_back(_tokens[++tmp]);
            index++;
        }

        return buffer;
    }

    // Intends to add support for more languages
    // TODO: need to improve design here
    const std::set<std::string> &Parser::scanDependencies(std::unique_ptr<SynAnalysis>& sa)
    {
        int size = _tokens.size();

        if (_tokens.empty())
            return {};

        while (_current < (size - 1))
        {
            sa->parse(this);
        }

        return sa->deps();
    }

}
