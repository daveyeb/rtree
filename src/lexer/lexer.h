#ifndef __RT__LEXER_H__
#define __RT__LEXER_H__

#include "common.h"
#include "scanner/scanner.h"

namespace RTToken
{

    class Token;

    class Lexer : public Scanner<char>
    {
    public:
        Lexer(const std::string b);
        virtual ~Lexer();

        char current() const;
        char next();

        std::vector<Token>& scanTokens();
        std::string peek(size_t n) const;

    private:
        std::string _buffer;
    };

} // namespace RTToken

#endif