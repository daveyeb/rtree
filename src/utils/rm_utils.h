#ifndef RM_UTIL
#define RM_UTIL

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define TOK_SIZE 4906
#define PEK_SIZE 100

#define RM_DEFAULT_CAP 10
#define RM_STRING_SIZE_CAP 256
#define RM_INT_SIZE_CAP 4

#define RM_SUCCESS 0
#define RM_FAIL 1 

#include "../ds/rm_array.h"

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
    const int (*scan_numeric)(lexer *p, rm_array * a);

    // int (*scan_literal)(lexer *p, char **tokens);
    // int (*scan_punctuation)(lexer *p, char **tokens);
    // int (*scan_identifier)(lexer *p, char **tokens);
    // int (*skip_comment)(lexer *p, char **tokens);
};

typedef struct language
{
    struct rules_vtable rules;
    const char *name;
} language;

int isbinary(int c)
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
static inline int _match(lexer *lex, int *found, char expected, int is_case);

static inline int _peek(lexer *lex, char *result, int n_pos)
{
    int buf_len;
    int temp_curr;

    buf_len = strlen(lex->buf);
    temp_curr = lex->current;

    if ((n_pos + temp_curr) >= buf_len) // end of line reached;
        return 1;

    strncpy(result, lex->buf + (++temp_curr), n_pos);

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

    if (lex == NULL)
        return 1;

    buf_len = strlen(lex->buf);

    if (lex->current < buf_len)
        *c = lex->buf[++lex->current];

    return 0;
}

static inline int _match(lexer *lex, int *found, char expected, int is_case)
{ // idgt
    int buf_len;
    int curr;
    int tmp_char;

    buf_len = strlen(lex->buf);
    *found = 0;
    curr = lex->current;

    tmp_char = lex->buf[curr];

    if(is_case){
        tmp_char = toupper(lex->buf[curr]);
    }

    if ((curr >= buf_len) || (tmp_char != expected))
        return 1;
    else{
        *found = 1;
        ++lex->current;
    }

    return 0;
}

#endif // RM_UTIL
