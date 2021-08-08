#include "JavaScript.h"
#include "parser/parser.h"
#include "token.h"

void _JavaScript(Parser *const p, std::set<std::string> &deps)
{

    std::vector<Token> buffer;

    Token t = p->getCurrent();
    Type tt = t.getType();

    p->next();

    if (tt == UNKNOWN)
        return;

    if (!(tt == IMPORT || tt == REQUIRE))
        return;

    switch (tt)
    {
    case IMPORT:
        tt = STRING;
        break;
    case REQUIRE:
        tt = C_PAREN;
        break;
    default:
        return;
    }

    while (1)
    {
        if (IS_EQ(t.getLexeme(), ";"))
            break;

        if (IS_EQ(t.getLexeme(), ":"))
            break;

        if (tt == STRING)
            if (IS_EQ(t.getLexeme(), "="))
                break;

        if (tt == C_PAREN)
            if (IS_EQ(t.getLexeme(), ")"))
                break;

        if (tt == STRING)
        {
            buffer = p->peek(1);
            if (!buffer.size() ||
                buffer[0].getType() != COMMA)
                break;
        }

        if (tt == C_PAREN)
        {
            buffer = p->peek(1);
            if (!buffer.size() ||
                buffer[0].getType() != O_PAREN)
                break;
        }

        t = p->next();

        if (t.getType() == UNKNOWN)
            break;

        if (t.getType() == STRING)
        {
            deps.insert(t.getLexeme());
            break;
        }
    }
}