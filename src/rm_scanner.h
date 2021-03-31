#ifndef RM_SCANNER
#define RM_SCANNER

#include "rm_spec.h"

static inline int scan_token(rm_lexer *lexer, rm_list *tokens, rm_language *lang);

static inline int scan_token(rm_lexer *lexer, rm_list *tokens, rm_language *lang)
{
    int skip; // needed to skip whitespaces and already consumed chars

    while (lexer->current < lexer->length)
    {

        lang->rules.scan_numeric(lexer, tokens);
        lang->rules.scan_identifier(lexer, tokens);
        lang->rules.skip_comment(lexer, tokens);
        lang->rules.scan_punctuation(lexer, tokens);
        lang->rules.scan_literal(lexer, tokens);

        _next_char(lexer, &skip);
    }

    return 0;
}

#endif // RM_SCANNER
