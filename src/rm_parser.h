#ifndef RM_PARSER
#define RM_PARSER

#include "rm_utils.h"

int rm_ppeek(rm_parser *parser, token *t, int npos);
int rm_pmatch(rm_parser *parser, token *t, token expected);
int rm_pcurrt(rm_parser *parser, token *t);
int rm_pnextt(rm_parser *parser, token *t);

int rm_ppeek(rm_parser *parser, token *t, int npos)
{

    int blen;
    int curr;

    if (parser == NULL)
        return 1;

    blen = parser->tbuffer.size();
    curr = parser->current;

    if ((curr + npos) >= blen)
        return 1;

    return 0;
}

int rm_pmatch(rm_parser *parser, token *t, token expected)
{
    int blen;
    int curr;
    token tok;

    if (parser == NULL || t == NULL)
        return 1;

    t = NULL;
    blen = parser->tbuffer.size();
    curr = parser->current;
    tok = parser->tbuffer[curr];

    // if ((curr >= blen) || (tok != expected))
    //     return 1;

    // *t = 1;
    ++parser->current;

    return 0;
}

int rm_pcurrt(rm_parser *parser, token *t)
{
    int blen;
    int curr;

    if (parser == NULL || t == NULL)
        return 1;

    blen = parser->tbuffer.size();
    curr = parser->current;

    // if (curr < blen)
    //     t = &parser->tbuffer[curr];
    // else
    //     t = NULL;

    return 0;
}

int rm_pnextt(rm_parser *parser, token *t){
    int blen;
    int curr;

    if (parser == NULL || t == NULL)
        return 1;

    blen = parser->tbuffer.size();
    curr = parser->current;

    // if (curr < blen)
    //     *t = parser->tbuffer[++curr];
    // else
    //     *t = 0;

    parser->current = curr;

    return 0;

}

#endif // rm_parser