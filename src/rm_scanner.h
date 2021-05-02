#ifndef RM_SCANNER
#define RM_SCANNER

#include "rm_utils.h"
#include "rm_types.h"
#include "rm_string.h"

/*
    Scanner funcs. 
        1. rm_s_peek()
        2. rm_s_match();
        3. rm_s_curr();
        4. rm_s_next();

        *. scan_tokens();

*/

int rm_s_peek(rm_s *scanner, rm_str &result, const int npos)
{
    int length;
    int current;

    if (scanner == NULL)
        return 1;

    length = scanner->buffer.length();
    current = scanner->current;

    if ((current + npos) >= length)
        return 1;

    result = scanner->buffer.substr(++current, npos);

    return 0;
}

int rm_s_match(rm_s *scanner, int &result, char c)
{
    int length;
    int current;
    int ch;

    if (scanner == NULL)
        return 1;

    result = 0;
    length = scanner->buffer.length();
    current = scanner->current;
    ch = scanner->buffer[current];

    if ((current >= length) || (ch != c))
        return 1;

    result = 1;
    ++scanner->current;

    return 0;
}

int rm_s_curr(rm_s *scanner, int &c)
{
    int length;
    int current;

    if (scanner == NULL)
    {
        return 1;
    }

    length = scanner->buffer.length();
    current = scanner->current;

    if (current < length)
        c = scanner->buffer[current];
    else
        c = 0;

    return 0;
}

int rm_s_next(rm_s *scanner, int &c)
{
    int length;
    unsigned int *current;

    if (scanner == NULL)
        return 1;

    length = scanner->buffer.length();
    current = &scanner->current;

    ++(*current);
    if (*current < length)
        c = scanner->buffer[*current];
    else
        c = 0;

    return 0;
}

rm_func int scan_tokens(rm_s *scanner, rm_ts &toks, rm_ss spec)
{
    int length;
    int ch;
    int prev;

    if (scanner == NULL)
        return 1;

    scanner->current = 0;
    toks.clear();
    int i = 0;
    while (scanner->current < scanner->buffer.length())
    {
        spec._identifier(scanner, toks);
        spec._comment(scanner);
        spec._punctuation(scanner, toks);
        spec._literal(scanner, toks);

        rm_s_curr(scanner, ch);
    }

    return 0;
}

#endif // !RM_SCANNER
