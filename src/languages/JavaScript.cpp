#include "languages/Javascript.h"
#include "parser/parser.h"
#include "token/token.h"

namespace RTree
{
    
    RTJavaScript::RTJavaScript(){}
    RTJavaScript::~RTJavaScript(){}

    std::set<std::string> RTJavaScript::deps() const {
        return _deps;
    }

    void RTJavaScript::parse(Parser *const p, std::set<std::string> &str)
    {

        std::vector<Token> buffer;

        Token t = p->current();
        int tt = t.type();

        switch (tt)
        {
        case IMPORT:
            tt = STRING;
            break;
        case REQUIRE:
            tt = C_PAREN;
            break;
        default:
            p->next();
            return;
        }

        while (1)
        {

            if (iseq(t.lexeme(), ";"))
                break;

            if (iseq(t.lexeme(), ":"))
                break;

            if (tt == STRING)
                if (iseq(t.lexeme(), "="))
                    break;

            if (tt == C_PAREN)
                if (iseq(t.lexeme(), ")"))
                    break;

            if (tt == STRING)
            {
                buffer = p->peek(1);

                if (!buffer.size() ||
                    buffer[0].type() == COMMA)
                    break;

                tt = RT_EOF;
            }

            if (tt == C_PAREN)
            {

                buffer = p->peek(1);

                if (!buffer.size() ||
                    buffer[0].type() != O_PAREN)
                    break;

                tt = RT_EOF;
            }
            t = p->next();

            if (t.type() == UNKNOWN)
                break;

            if (t.type() == STRING)
            {
                str.insert(t.lexeme());
                break;
            }
        }
        p->next();
    }

}
