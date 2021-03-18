#ifndef RM_SPEC_JAVA
#define RM_SPEC_JAVA

#include "../utils/rm_utils.h"
#include "../ds/rm_array.h"

const int _numeric(lexer *lexer, rm_array *tokens);
const int _literal(lexer *lexer, rm_array *tokens);
const int _punctuation(lexer *lexer, rm_array *tokens);
const int _identifier(lexer *lexer, rm_array *tokens);
const int _comment(lexer *lexer, rm_array *tokens);

const int _numeric(lexer *lexer, rm_array *tokens)
{

    int curr;                     // current char
    int t_cnt;                    // token char count
    int p_cnt;                    // period count -- for decimal numerals
    int status;                   // function status
    int (*ctype_func_ptr)(int c); // function pointer

    char token[TOK_SIZE]; // token buffer
    char peek[PEK_SIZE];  // peek buffer

    curr = 0;
    p_cnt = 0;
    t_cnt = 0;

    memset(token, 0, TOK_SIZE);
    memset(peek, 0, PEK_SIZE);

    if (lexer == NULL || tokens == NULL)
        return RM_FAIL;

    _curr_char(lexer, &curr);

    status = isdigit(curr);

    if (status)
    {
        while (isdigit(curr) || curr == '.')
        {
            if (p_cnt > 1)
                break;
            if (curr == '.')
                ++p_cnt;

            token[t_cnt++] = curr;
            _next_char(lexer, &curr);

            if (curr == '_') // skip underscores
                while (!_match(lexer, &status, '_', 0))
                    ;

            _curr_char(lexer, &curr);
        }

        if (curr == ' ')
            goto t_postfix;

        if (t_cnt != 1 && token[0] != '0')
            goto t_postfix;

        if (curr != 'x' && curr != 'b')
            goto t_postfix;

        if (p_cnt >= 1)
            goto t_postfix;

        ctype_func_ptr = (curr == 'x') ? &isxdigit : &isbinary;

        token[t_cnt++] = curr;    // add to token buffer
        _next_char(lexer, &curr); // consume x or b

        while (ctype_func_ptr(curr))
        {
            token[t_cnt++] = curr;
            _next_char(lexer, &curr);

            if (curr == '_') // skip underscores
                while (!_match(lexer, &status, '_', 0))
                    ;
            _curr_char(lexer, &curr);
        }
    }
    else
    {

        _peek(lexer, &peek[0], 1);

        if (curr != '.')
            goto t_exit;

        if (isdigit(peek[0]) == 0)
            goto t_exit;

        token[t_cnt++] == curr;
        _next_char(lexer, &curr);

        printf("here %s\n", curr);

        while (isdigit(curr))
        {
            token[t_cnt++] == curr;
            _next_char(lexer, &curr);
        }
    }

t_postfix:

    _match(lexer, &status, 'f', 0);

    if (!status)
        _match(lexer, &status, 'L', 1);

    if (!status)
        goto t_persist;

    token[t_cnt++] = curr;

t_persist:
    // add to array
    printf("number --> %s\n", token);

t_exit:

    return RM_SUCCESS;
}

#endif // RM_SPEC_JAVA
