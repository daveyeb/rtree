#ifndef RM
#define RM

#include "rm_utils.h"

#include "rm_srules.h"

static inline int scan_tokens(rm_scanner *scanner, std::vector<rm_token> tokens);

static inline int scan_tokens(rm_scanner *scanner, std::vector<rm_token> tokens, rm_srules rules)
{
    int adch;

    if (scanner == NULL)
        return 1;

    while (scanner->current < scanner->length)
    {
        rules._numeric(scanner, tokens);
        rules._identifier(scanner, tokens);
        rules._comment(scanner, tokens);
        rules._punctuation(scanner, tokens);
        rules._literal(scanner, tokens);

        // skip whitespaces and already consumed characters
        rm_snextc(scanner, &adch);
    }

    return 0;
}


#endif // rm