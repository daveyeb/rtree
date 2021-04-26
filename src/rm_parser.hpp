#ifndef RM_PARSER
#define RM_PARSER

#include "rm_utils.hpp"

rm_func int scan_statement(rm_p *parser, rm_sts &stmts, rm_ps spec)
{
    rm_t tok;

    if (parser == NULL)
        return 1;

    parser->current = 0;

    while (parser->current < parser->tokens.size())
    {
        spec._javascript(parser, stmts);
        rm_p_next(parser, tok);
    }

    return 0;
}

#endif // !RM_PARSER