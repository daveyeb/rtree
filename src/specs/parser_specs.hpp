#ifndef PARSER_SPECS
#define PARSER_SPECS

#include "../rm_utils.hpp"

int _javascript(rm_p *parser, rm_sts &stmts)
{
    rm_t tok;
    rm_ts toks;
    rm_st stmt;


    if (parser == NULL)
        return 1;

    rm_p_curr(parser, tok);

    if (tok.type != IMPORT)
        return 1;

    while (tok.type != SEMICOLON)
    {
       
        rm_p_peek(parser, toks, 1);
        if (toks[0].type == SEMICOLON)
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
            rm_p_next(parser, tok); // consume close parenthesis
            break;

        default:
            break;
        }

        rm_p_next(parser, tok);
    }

    stmts.push_back(stmt);

    return 0;
}

#endif // !PARSER_SPECS