#include "spec.h"
#include "lexer/lexer.h"
#include "token/token.h"

void Spec::identifier(Lexer *const l, std::vector<Token> &tokens)
{
    char ch;
    std::string buffer;
    std::string lower;

    std::vector<std::string> targetIds =
        {"from", "import", "use", "load", "require", "include"};

    ch = l->getCurrent();

    if (isspace(ch) || IS_CTRL(ch))
        l->next();

    if (!IS_ALNUM(ch))
        return;

    while (IS_ALNUM(ch))
    {
        if (ch == -1)
            break;

        buffer += ch;
        ch = l->next();
    }

    lower = TO_LOWER(buffer);
    int found =
        std::find(targetIds.begin(),
                  targetIds.end(), lower) -
        targetIds.begin();

    // test for end value or non elements
    if (found > 5)
        tokens.push_back(Token(LITERAL, buffer));
    else
        tokens.push_back(Token((Type)(++found), buffer));
}

void Spec::comment(Lexer *const l)
{
    char ch, pch;

    ch = l->getCurrent();
    pch = l->peek(1)[0];

    if (isspace(ch) || IS_CTRL(ch))
        l->next();

    if (ch != '/')
        return;

    if (pch == '/')
    {
        ch = l->next();

        while (ch != -1 && ch != '\n')
            ch = l->next();

        return;
    }

    if (pch == '*')
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

void Spec::literal(Lexer *const l, std::vector<Token> &tokens)
{
    char ch, qch;
    std::string buffer;

    ch = l->getCurrent();

    if (isspace(ch) || IS_CTRL(ch))
        l->next();

    if (!IS_SDB(ch))
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

    tokens.push_back(Token(STRING,
                            buffer,
                            std::
                                string("\"" + buffer + "\"")));

    l->next();
}

void Spec::punctuation(Lexer *const l, std::vector<Token> &tokens)
{
    char ch, pch;

    const std::string pts = "<>,*;{}()#.";

    ch = l->getCurrent();

    if (isspace(ch) || IS_CTRL(ch))
        l->next();

            if (!ispunct(ch) || IS_SDB(ch) || ch == '/') return;

    if (!STR_CON(pts, std::string(1, ch)))
        tokens.push_back(Token(SYMBOL, std::string(1, ch)));
    else
        tokens.push_back(Token((Type)ch, std::string(1, ch)));

    if (ch == '#')
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