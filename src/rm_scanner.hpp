#ifndef RM_SCANNER
#define RM_SCANNER

#include "rm_utils.hpp"

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
