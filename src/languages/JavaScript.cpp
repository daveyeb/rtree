#include "JavaScript.h"
#include "parser/parser.h"
#include "token/token.h"

void JavaScript::parse(Parser *const p, std::set<std::string> &mods)
{

    std::vector<Token> buffer;

    Token t = p->getCurrent();
    Type tt = t.getType();

    switch (tt)
    {
    case IMPORT:
        tt = STRING;
        break;
    case REQUIRE:
        tt = C_PAREN;
        break;
    default:
#if PARSER
        std::cout << "here " << t.getLexeme() << "\n";
#endif
        p->next();
        return;
    }
#if PARSER
    size_t tmp = p->curr();
#endif

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
                buffer[0].getType() == COMMA)
                break;

            tt = RT_EOF;
        }

        if (tt == C_PAREN)
        {

            buffer = p->peek(1);

            if (!buffer.size() ||
                buffer[0].getType() != O_PAREN)
                break;

            tt = RT_EOF;
        }
#if PARSER
std::cout << "Here" << std::endl;
#endif
        t = p->next();

        if (t.getType() == UNKNOWN)
            break;



        if (t.getType() == STRING)
        {
            mods.insert(t.getLexeme());
            break;
        }

#if PARSER
        std::cout << "b " << t.getLexeme() << "--\n";
        assert (tmp != p->curr());
        
        tmp = p->curr();
#endif
    }
    p->next();
}