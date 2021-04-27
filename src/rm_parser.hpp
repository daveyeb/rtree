#ifndef RM_PARSER
#define RM_PARSER

#include "rm_utils.hpp"

rm_func int scan_statement(rm_p *parser, rm_st &stmt, rm_ps spec)
{
    rm_t tok;

    if (parser == NULL)
        return 1;

    parser->current = 0;
    stmt.imports.clear();

    while (parser->current < parser->tokens.size())
    {
        printf("string %s\n", tok.lexeme.c_str());
        spec._javascript(parser, stmt);
        rm_p_next(parser, tok);
    }

    return 0;
}

#endif // !RM_PARSER