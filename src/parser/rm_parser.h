#ifndef RM_PARSER
#define RM_PARSER

#include "../rules/rm_spec_java.h"

static inline int scan_token(lexer *lex, struct language *lang, char **tokens);

static inline int scan_token(lexer *lex, struct language *lang, char **tokens)
{

    while (lex->current < lex->length)
    {
        int start = lex->current;

        lang->rules.scan_identifier(lex);
        lang->rules.scan_literal(lex);
        lang->rules.scan_numeric(lex);
        lang->rules.scan_punctuation(lex);

        _next_char(lex, 0);
    }

    return 0;
}

#endif // RM_PARSER