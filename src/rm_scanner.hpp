#ifndef RM_SCANNER
#define RM_SCANNER

#include "rm_utils.hpp"

rm_func int scan_tokens(rm_s *scanner, rm_ts &toks, rm_ss spec)
{
    int length;
    int ch;

    if (scanner == NULL)
        return 1;

    scanner->current = 0;
    toks.clear();

    while (scanner->current < scanner->buffer.length())
    {

        spec._identifier(scanner, toks);
        spec._regexp(scanner);
        spec._comment(scanner);
        spec._punctuation(scanner, toks);
        spec._literal(scanner, toks);

        rm_s_next(scanner, ch);
    }

    return 0;
}

#endif // !RM_SCANNER
