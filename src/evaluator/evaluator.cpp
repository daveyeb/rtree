#include "evaluator.h"
#include "lexer/lexer.h"
#include "token/token.h"

namespace RTToken
{

    Evaluator::Evaluator()
    {
        // these ids are ordered for a reason
        ids.push_back("from");
        ids.push_back("import");
        ids.push_back("use");
        ids.push_back("load");
        ids.push_back("require");
        ids.push_back("include");

        pts = "<>,*;{}()#.";
    }

    Evaluator::~Evaluator() {}

    void Evaluator::identifier(Lexer *const l, std::vector<Token> &tokens) const
    {
        char ch;
        std::string buffer, lBuffer;

        ch = l->current();

        if (isspace(ch) || iscntrl(ch))
            l->next();

        if (!isalnum_mod(ch))
            return;

        while (isalnum_mod(ch))
        {
            if (ch == -1)
                break;

            buffer += ch;
            ch = l->next();
        }

        // normalize token by lowering case
        // then find if its part of targetted ids
        // idealy, we only want tokens in targetted ids
        lBuffer = lower(buffer);
        int found =
            std::find(ids.begin(), ids.end(), lBuffer) - ids.begin();

        // test for end value or non elements
        if (found > 5)
            tokens.push_back(Token(LITERAL, buffer));
        else
            tokens.push_back(Token((Type)(++found), buffer));
    }

    // this function needed to skip comments
    void Evaluator::comment(Lexer *const l) const
    {
        char ch, pch;

        ch = l->current();
        pch = l->peek(1)[0];

        if (isspace(ch) || iscntrl(ch))
            l->next();

        if (ch != '/')
            return;

        if (pch == '/') // checks for single line comments
        {
            ch = l->next();

            while (ch != -1 && ch != '\n')
                ch = l->next();

            return;
        }

        if (pch == '*') // checks for multi line comments
        {
            l->next();

            while (ch != -1)
            {
                ch = l->next();
                pch = l->peek(1)[0];

                if (ch == '*' && pch == '/')
                {
                    l->next();
                    l->next();
                    break;
                }
            }
            return;
        }

        l->next();
    }

    void Evaluator::literal(Lexer *l, std::vector<Token> &tokens) const
    {
        char ch, qch;
        std::string buffer;

        ch = l->current();

        if (isspace(ch) || iscntrl(ch))
            l->next();

        if (!issdb(ch))
            return;

        qch = ch;
        ch = l->next();

        while (ch != qch)
        {
            if (ch == -1)
                break;

            if ((qch == 39 || qch == 34) && ch == '\n')
                break;

            if (ch == 92)
            {
                buffer += ch;
                ch = l->next();
                buffer += ch;
            }
            else
                buffer += ch;

            ch = l->next();
        }

        tokens.push_back(Token(STRING, buffer));

        l->next();
    }

    void Evaluator::punctuation(Lexer *l, std::vector<Token> &tokens) const
    {
        char ch, pch;

        ch = l->current();

        if (isspace(ch) || iscntrl(ch))
            l->next();

        if (!ispunct(ch) || issdb(ch) || ch == '/')
            return;

        if (!strcon(pts, std::string(1, ch)))
            tokens.push_back(Token(SYMBOL, std::string(1, ch)));
        else
            tokens.push_back(Token((Type)ch, std::string(1, ch)));

        if (ch == '#') /// rids of shebangs, we dont need!
        {
            pch = l->peek(1)[0];

            if (pch == '!')
            {
                while (ch != 32)
                {
                    ch = l->next();
                    if (ch == -1)
                        break;
                }
            }
        }

        l->next();
    }

}
