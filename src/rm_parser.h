#ifndef RM_PARSER
#define RM_PARSER

#include "rm_utils.h"

/*
    Parser functions 
        1. rm_p_match()
        2. rm_p_curr()
        3. rm_p_peek()
        4. rm_p_next()
        5. rm_p_prev()

        *. scan_statements()

*/

int rm_p_match(rm_p *parser, rm_tt tt, int &result)
{
    int size;
    int current;

    rm_t tok;

    if (parser == NULL)
        return 1;

    result = 0;
    size = parser->tokens.size();
    current = parser->current;
    tok = parser->tokens[current];

    if ((current >= size) || tok.type != tt)
        return 1;

    result = 1;
    ++parser->current;

    return 0;
}

int rm_p_curr(rm_p *parser, rm_t &tok)
{
    int size;
    int current;

    if (parser == NULL)
        return 1;

    size = parser->tokens.size();
    current = parser->current;

    if (current < size)
        tok = parser->tokens[current];

    return 0;
}

int rm_p_peek(rm_p *parser, rm_ts &result, int npos)
{
    int size;
    int current;
    int index;

    if (parser == NULL)
        return 1;

    size = parser->tokens.size();
    current = parser->current;
    result.clear();

    if ((current + npos) >= size)
        return 1;

    index = 0;
    while (index < npos)
    {
        result.push_back(parser->tokens[++current]);
        ++index;
    }

    return 0;
}

int rm_p_next(rm_p *parser, rm_t &tok)
{
    int size;
    unsigned int *current;

    if (parser == NULL)
        return 1;

    size = parser->tokens.size();
    current = &parser->current;

    ++(*current);

    if (*current < size)
        tok = parser->tokens[*current];

    return 0;
}

int rm_p_prev(rm_p *parser, rm_t &tok)
{
    int size;
    int current;

    if (parser == NULL)
        return 1;

    size = parser->tokens.size();
    current = parser->current;

    --current;
    if (current < size && current < 0)
        tok = parser->tokens[current];

    return 0;
}

rm_func int scan_statement(rm_p *parser, rm_st &stmt, rm_ps spec)
{
    rm_t tok;

    if (parser == NULL)
        return 1;

    parser->current = 0;
    stmt.imports.clear();

    int i = 0;
    while (parser->current < parser->tokens.size())
    {
        spec._javascript(parser, stmt);
    }

    return 0;
}

#endif // !RM_PARSER