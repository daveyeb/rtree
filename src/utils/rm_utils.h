#ifndef RM_UTIL
#define RM_UTIL

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

typedef enum token_t
{
    RC_INDENTIFIER,
    RC_LITERAL,
    RC_KEYWORD,
    RC_PUNCTUATION,
    RC_ENDOFFILE
} token_t;

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
} lexer;

struct rules_vtable
{
    int (*scan_numeric)(lexer *p, char **tokens);
    int (*scan_literal)(lexer *p, char **tokens);
    int (*scan_punctuation)(lexer *p, char **tokens);
    int (*scan_identifier)(lexer *p, char **tokens);
    int (*skip_comment)(lexer *p, char **tokens);
};

typedef struct language
{
    struct rules_vtable rules;
    const char *name;
} language;

int isbinary(char c)
{
    return (c == 48 || c == 49);
}

int isalnumundol(char c)
{
    return isalnum(c) || c == 95 || c == 36;
}

static inline int _peek(lexer *lex, char *result, int n_pos);
static inline int _curr_char(lexer *lex, int *c);
static inline int _next_char(lexer *lex, int *c);
static inline int _match(lexer *lex, char expected, int *found);

static inline int _peek(lexer *lex, char *result, int n_pos)
{
    int buf_len;
    int temp_curr;

    buf_len = strlen(lex->buf);
    temp_curr = lex->current;

    if ((n_pos + temp_curr) >= buf_len) // end of line reached;
        return 1;

    strncpy(result, lex->buf + (n_pos + temp_curr), n_pos);
    // printf("peek result %s", result);

    return 0;
}

static inline int _curr_char(lexer *lex, int *c)
{
    int buf_len;

    buf_len = strlen(lex->buf);

    if (lex->current < buf_len)
        *c = lex->buf[lex->current];

    return 0;
}

static inline int _next_char(lexer *lex, int *c)
{
    int buf_len;

    buf_len = strlen(lex->buf);

    if (lex->current < buf_len)
        *c = lex->buf[++lex->current];

    return 0;
}

static inline int _match(lexer *lex, char expected, int *found)
{ // idgt
    int buf_len;
    int curr;

    buf_len = strlen(lex->buf);
    *found = 0;
    curr = lex->current;

    if ((curr >= buf_len) || (lex->buf[curr] != expected))
        return 1;
    else
        *found = 1;

    return 0;
}

#endif // RM_UTIL