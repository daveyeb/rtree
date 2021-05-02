#ifndef PARSER_SPEC
#define PARSER_SPEC

#include "rm_string.h"
#include "rm_types.h"
#include "rm_utils.h"

int _javascript(rm_p *parser, rm_st &stmt)
{
    int status;

    rm_t tch;
    rm_t tmp;
    rm_t tok;
    rm_ts toks;

    if (parser == NULL)
        return 1;

    rm_p_curr(parser, tok);

    status = tok.type == IMPORT;
    status |= tok.type == REQUIRE;

    if (tok.type == IMPORT)
        tch.type = SEMICOLON;

    if (tok.type == REQUIRE)
        tch.type = CPARENS;

    if (!status)
    {
        rm_p_next(parser, tok);
        return 1;
    }

    while (tok.type != tch.type)
    {
        rm_p_peek(parser, toks, 1);
        if (tok.type == STRING)
            if (toks[0].type == tch.type)
            {
                stmt.imports.push_back(tok.lexeme);
                rm_p_next(parser, tok);
                break;
            }

        switch (tok.type)
        {
        case FROM:
            rm_p_next(parser, tok);
            stmt.imports.push_back(tok.lexeme);
            break;
        case OPARENS:
            rm_p_next(parser, tok);
            stmt.imports.push_back(tok.lexeme);
            break;

        default:
            break;
        }

        rm_p_next(parser, tok);
    }

    rm_p_next(parser, tok);

    return 0;
}

#endif // !PARSER_SPEC