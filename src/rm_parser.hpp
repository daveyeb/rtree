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

    printf("token size %d\n", parser->tokens.size());
    fflush(stdin);

    while (parser->current < parser->tokens.size())
    {
        printf("----------\n");
        fflush(stdin);
        printf("string %d\n", tok.type);
        fflush(stdin);
        spec._javascript(parser, stmt);

        printf("leftover %d\n", tok.type);
        fflush(stdin);
        rm_p_next(parser, tok);

        printf("leftover current %d\n", parser->current);
        fflush(stdin);
    }

    return 0;
}

#endif // !RM_PARSER