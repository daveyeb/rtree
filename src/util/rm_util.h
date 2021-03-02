#ifndef RM_UTIL
#define RM_UTIL

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

enum token_t
{
    RC_INDENTIFIER,
    RC_LITERAL,
    RC_KEYWORD,
    RC_PUNCTUATION,
    RC_ENDOFFILE
};

typedef struct token
{
    token_t type;
    char *value;
    char *raw;
} _rc_token_t;

typedef struct lexer
{
    unsigned int start;
    unsigned int current;
    unsigned int length;
    char *buf;
};

struct rules_vtable
{
    int (*scan_numeric)(lexer *p);
    int (*scan_literal)(lexer *p);
    int (*scan_punctuation)(lexer *p);
    int (*scan_identifier)(lexer *p);
};

struct language
{
    struct rules_vtable rules;
    const char *name;
};

static inline int _peek(lexer *lex, char *result, int n_pos);
static inline int _curr_char(lexer *lex, int c);
static inline int _next_char(lexer *lex, int c);
static inline int _match(lexer *lex, char expected, int found);
// static inline int _is_decimal(lexer *lex, char target);

static inline int _peek(lexer *lex, char *result, int n_pos)
{
    int buf_len;
    int temp_curr;

    buf_len = strlen(lex->buf);
    temp_curr = lex->current;

    if ((n_pos + temp_curr) >= buf_len) // end of line reached;
        return 1;

    strncpy(result, lex->buf + temp_curr, n_pos);

    return 0;
}

static inline int _curr_char(lexer *lex, int c)
{
    int buf_len;

    buf_len = strlen(lex->buf);

    if (lex->current < buf_len)
        c = lex->buf[lex->current];

    return 0;
}

static inline int _next_char(lexer *lex, int c)
{
    int buf_len;

    buf_len = strlen(lex->buf);

    if (lex->current < buf_len)
        c = lex->buf[lex->current++];

    return 0;
}

static inline int _match(lexer *lex, char expected, int found)
{ // idgt
    int buf_len;
    int curr;

    buf_len = strlen(lex->buf);
    found = 0;
    curr = lex->current;

    if ((curr >= buf_len) || (lex->buf[curr] != expected))
        return 1;
    else
        found = 1;

    return 0;
}

// static inline int _is_decimal(lexer *lex, char target){

//     return 0;
// }

#endif // RM_UTIL