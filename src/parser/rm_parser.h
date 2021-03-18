#ifndef RM_PARSER
#define RM_PARSER

#include "../rules/rm_spec_java_refined.h"

static inline int scan_token(lexer *lex, struct language *lang, rm_array * a);

static inline int scan_token(lexer *lex, struct language *lang, rm_array * a)
{
    int tmp_char; // needed to skip whitespaces and illegal chars

    while (lex->current < lex->length)
    {
        int start = lex->current;

        lang->rules.scan_numeric(lex, a);

        // lang->rules.scan_identifier(lex, tokens);
        // lang->rules.skip_comment(lex, tokens);
        // lang->rules.scan_punctuation(lex, tokens);
        // lang->rules.scan_literal(lex, tokens);

        _next_char(lex, &tmp_char);
    }

    return 0;
}

#endif // RM_PARSER
