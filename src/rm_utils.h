#ifndef RM_UTIL
#define RM_UTIL

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define TOK_SIZE 4906
#define PEK_SIZE 100

#define RM_SUCCESS 0
#define RM_FAIL 1

#include "rm_list.h"

typedef enum type
{
    // keywords
    FROM,
    IMPORT,
    AS,
    USE,
    LOAD,
    REQUIRE,
    INCLUDE,
    // puncts.
    LTHAN,
    GTHAN,
    COMMA,
    ASTERISKS,
    SEMICOLON,
    OCBRACKS,
    CCBRACKS,
    OPARENS,
    CPARENS,
    DQUOTES,
    SQUOTES,
    POUND,
    FSLASH,
    // literals.
    STRING,
    NUMBER,
    LITERAL,
} rm_token_t;

typedef struct token
{
    int type;
    char value[256];
    char raw[256];
} rm_token;

typedef struct lexer
{
    unsigned int start;
    unsigned int current;
    unsigned int length;
    char *buf;
} rm_lexer;

struct rules_vtable
{
    const int (*scan_numeric)(rm_lexer *p, rm_list *tokens);
    const int (*scan_identifier)(rm_lexer *p, rm_list *tokens);
    const int (*skip_comment)(rm_lexer *p, rm_list *tokens);
    const int (*scan_punctuation)(rm_lexer *p, rm_list *tokens);
    const int (*scan_literal)(rm_lexer *p, rm_list *tokens);
};

typedef struct language
{
    struct rules_vtable rules;
    const char *name;
} rm_language;

int isbinary(int c)
{
    return (c == 48 || c == 49);
}

int isalnumundol(char c)
{
    return isalnum(c) || c == 95 || c == 36;
}

static inline int _peek(rm_lexer *lex, char *result, int n_pos);
static inline int _curr_char(rm_lexer *lex, int *c);
static inline int _next_char(rm_lexer *lex, int *c);
static inline int _match(rm_lexer *lex, int *found, char expected, int is_case);

static inline int _peek(rm_lexer *lex, char *result, int n_pos)
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

static inline int _curr_char(rm_lexer *lex, int *c)
{
    int buf_len;

    buf_len = strlen(lex->buf);

    if (lex->current < buf_len)
        *c = lex->buf[lex->current];
    else
        *c = 0;

    return 0;
}

static inline int _next_char(rm_lexer *lex, int *c)
{
    int buf_len;

    if (lex == NULL)
        return 1;

    buf_len = strlen(lex->buf);
    if (lex->current < buf_len)
        *c = lex->buf[++lex->current];
    else
        *c = 0;

    return 0;
}

static inline int _match(rm_lexer *lex, int *found, char expected, int is_case)
{ // idgt
    int buf_len;
    int curr;
    int tmp_char;

    buf_len = strlen(lex->buf);
    *found = 0;
    curr = lex->current;

    tmp_char = lex->buf[curr];

    if (is_case)
    {
        tmp_char = toupper(lex->buf[curr]);
    }

    if ((curr >= buf_len) || (tmp_char != expected))
        return 1;
    else
    {
        *found = 1;
        ++lex->current;
    }

    return 0;
}

const int rm_get_filelist(rm_list *filelist, const char *path, int sym_links);
const int rm_screen_filelist(rm_list *filelist);

#endif // RM_UTIL
