#ifndef RM_PARSER
#define RM_PARSER

#include "rm_spec.h"

static inline int scan_token(lexer *lexer, struct language *lang, rm_array *tokens);

static inline int scan_token(lexer *lexer, struct language *lang, rm_array *tokens)
{
    int skip; // needed to skip whitespaces and illegal chars


    while (lexer->current < lexer->length)
    {
        int start = lexer->current;

        lang->rules.scan_numeric(lexer, tokens);
        lang->rules.scan_identifier(lexer, tokens);
        // printf("li skip %c\n", lexer->buf[lexer->current]);
        lang->rules.skip_comment(lexer, tokens);
        lang->rules.scan_punctuation(lexer, tokens);
        lang->rules.scan_literal(lexer, tokens);

        // if(start == lexer->current)
        
        // printf("skip %c %d\n", lexer->buf[lexer->current], start);
   
        _next_char(lexer, &skip);
    }

    return 0;
}

#endif // RM_PARSER
