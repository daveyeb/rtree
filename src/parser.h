#ifndef PARSER
#define PARSER

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

static inline int _peek(lexer *p, const char *target, int n_pos);
static inline int _curr_char(lexer *p, int n_pos);
static inline int _next_char(lexer *p, int n_pos);
static inline int _match(lexer *p, char c, int result);
static inline int _is_decimal(lexer *p, char c);

static inline int scan_numeric(void);
static inline int scan_literal(void);
static inline int scan_punctuation(void);
static inline int scan_indentifier(void);

static inline int scan_token(lexer *p, char **tokens);

static inline int scan_token(lexer *p, char **tokens)
{

    return 0;
}

#endif
