#ifndef RM_PARSER
#define RM_PARSER

#include "rm_utils.hpp"

rm_func int scan_statement(rm_p *parser, rm_sts &stmts, rm_ps spec)
{
    if (parser == NULL)
        return 1;

    while (parser->current < parser->tokens.size())
    {
        spec._javascript(parser, stmts);
    }

    return 0;
}

#endif // !RM_PARSER