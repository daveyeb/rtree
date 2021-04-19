#ifndef RM_PARSER
#define RM_PARSER

#include "rm_utils.h"

int rm_ppeek(rm_parser *parser, std::vector<token> &result, int npos);
int rm_pmatch(rm_parser *parser, int &result, token expected);
int rm_pcurrt(rm_parser *parser, token &t);
int rm_pnextt(rm_parser *parser, token &t);

int rm_ppeek(rm_parser *parser, std::vector<token> &result, int npos)
{
    int blen;
    int curr;
    int index;

    if (parser == NULL)
        return 1;

    blen = parser->tokens.size();
    curr = parser->current;

    if ((curr + npos) >= blen)
        return 1;

    result.clear();

    //copying
    index = 0;
    while (index < npos)
    {
        result.push_back(parser->tokens[++curr]);
        index++;
    }

    return 0;
}

int rm_pmatch(rm_parser *parser, int *result, token expected)
{
    int blen;
    int curr;
    token tok;

    if (parser == NULL || result == NULL)
        return 1;

    *result = 0;
    blen = parser->tokens.size();
    curr = parser->current;
    tok = parser->tokens[curr];

    if ((curr >= blen) || (!istokeq(tok, expected)))
        return 1;

    *result = 1;
    ++parser->current;

    return 0;
}

int rm_pcurrt(rm_parser *parser, token &t)
{
    int blen;
    int curr;

    if (parser == NULL)
        return 1;

    blen = parser->tokens.size();
    curr = parser->current;

    if (curr < blen)
        t = parser->tokens[curr];

    // printf("inside p curr %s\n", t.lexeme.c_str());

    return 0;
}

int rm_pnextt(rm_parser *parser, token &t)
{
    int blen;
    int curr;

    if (parser == NULL)
        return 1;

    blen = parser->tokens.size();
    curr = parser->current;

    if (curr < blen)
        t = parser->tokens[++curr];

    parser->current = curr;

    return 0;
}

#endif // rm_parser