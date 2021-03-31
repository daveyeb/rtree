#ifndef RM_SPEC
#define RM_SPEC

#include "rm_utils.h"
#include "rm_list.h"

const int _numeric(rm_lexer *lexer, rm_list *tokens);
const int _literal(rm_lexer *lexer, rm_list *tokens);
const int _punctuation(rm_lexer *lexer, rm_list *tokens);
const int _identifier(rm_lexer *lexer, rm_list *tokens);
const int _comment(rm_lexer *lexer, rm_list *tokens);

const int _numeric(rm_lexer *lexer, rm_list *tokens)
{

    int curr;                     // current char
    int t_cnt;                    // token char count
    int p_cnt;                    // period count -- for decimal numerals
    int status;                   // function status
    int (*ctype_func_ptr)(int c); // function pointer

    char t_buffer[TOK_SIZE]; // token buffer
    char p_buffer[PEK_SIZE]; // peek buffer

    rm_token token; // token

    if (lexer == NULL || tokens == NULL)
        return RM_FAIL;

    curr = 0;
    p_cnt = 0;
    t_cnt = 0;

    memset(t_buffer, 0, TOK_SIZE);
    memset(p_buffer, 0, PEK_SIZE);

    _curr_char(lexer, &curr);

    status = isdigit(curr);

    if (status)
    {
        while (isdigit(curr) || curr == '.' || curr == 'e' || curr == '-' || curr == '+')
        {
            if (p_cnt > 1)
                break;
            if (curr == '.')
                ++p_cnt;

            t_buffer[t_cnt++] = curr;
            _next_char(lexer, &curr);

            if (curr == '_') // skip underscores
                while (!_match(lexer, &status, '_', 0))
                    ;

            _curr_char(lexer, &curr);
        }

        if (curr == ' ')
            goto t_postfix;

        if (t_cnt != 1 && t_buffer[0] != '0')
            goto t_postfix;

        if (curr != 'x' && curr != 'b')
            goto t_postfix;

        if (p_cnt >= 1)
            goto t_postfix;

        ctype_func_ptr = (curr == 'x') ? &isxdigit : &isbinary;

        t_buffer[t_cnt++] = curr; // add to token buffer
        _next_char(lexer, &curr); // consume x or b

        while (ctype_func_ptr(curr))
        {
            t_buffer[t_cnt++] = curr;
            _next_char(lexer, &curr);

            if (curr == '_') // skip underscores
                while (!_match(lexer, &status, '_', 0))
                    ;
            _curr_char(lexer, &curr);
        }
    }
    else
    {

        _peek(lexer, &p_buffer[0], 1);

        if (curr != '.')
            goto t_exit;

        if (isdigit(p_buffer[0]) == 0)
            goto t_exit;

        t_buffer[t_cnt++] = curr;
        _next_char(lexer, &curr);

        while (isdigit(curr))
        {
            t_buffer[t_cnt++] = curr;
            _next_char(lexer, &curr);
        }
    }

t_postfix:

    _match(lexer, &status, 'f', 0);

    if (!status)
        _match(lexer, &status, 'L', 1);

    if (!status)
        goto t_persist;

    t_buffer[t_cnt++] = curr;

    // TODO : implement octal functionality

t_persist:
    // add to array
    token.type = NUMBER;
    snprintf(token.value, strlen(t_buffer) + 1, "%s", t_buffer);
    rm_list_add(tokens, &token);

    printf("number --> %s\n", t_buffer);

t_exit:

    return RM_SUCCESS;
}

const int _literal(rm_lexer *lexer, rm_list *tokens)
{
    int curr;   // current char
    int t_cnt;  // token char count
    int qt;     // quotation mark char
    int status; // func. status

    char t_buffer[TOK_SIZE]; // token buffer
    rm_token token;

    if (lexer == NULL || tokens == NULL)
        return RM_FAIL;

    curr = 0;
    t_cnt = 0;

    memset(t_buffer, 0, TOK_SIZE);

    _curr_char(lexer, &curr);

    if (curr != 34 && curr != 39)
        return RM_FAIL;

    qt = curr;
    _next_char(lexer, &curr);

    while (curr != qt)
    {

        if (curr == 92)
        { // consuming escape chars
            t_buffer[t_cnt++] = curr;
            _next_char(lexer, &curr);
            t_buffer[t_cnt++] = curr;
        }
        else
        {
            t_buffer[t_cnt++] = curr;
        }

        _next_char(lexer, &curr);
    }

    //add to token
    token.type = LITERAL;
    snprintf(token.value, strlen(t_buffer) + 1, "%s", t_buffer);
    snprintf(token.raw, strlen(t_buffer) + 3, "\"%s\"", t_buffer);

    rm_list_add(tokens, &token);
    printf("literal --> %s \n", t_buffer);

    return RM_SUCCESS;
}

const int _punctuation(rm_lexer *lexer, rm_list *tokens)
{
    int curr;   // current char
    int t_cnt;  // token char count
    int p_cnt;  // peek char count
    int status; // func. status

    rm_token *name = malloc(1);

    printf("address %d ", name->type);

    char token[TOK_SIZE];
    char peek[PEK_SIZE];

    const char *sing_pt = ";{}[](),";    // single punctuations std.
    const char *mix_pt = "<>=!+-*%&|^/"; // mix punctuations std.
    const char *id_pt = "+-<>&|:";       // identical punctuations std.

    if (lexer == NULL || tokens == NULL)
        return RM_FAIL;

    curr = 0;
    p_cnt = 0;
    t_cnt = 0;

    memset(token, 0, TOK_SIZE);
    memset(peek, 0, PEK_SIZE);

    _curr_char(lexer, &curr);

    if (ispunct(curr) == 0)
        return RM_FAIL;

    if (curr == 34 || curr == 39)
        return RM_FAIL;

    token[t_cnt++] = curr;

    if (strchr(sing_pt, curr) != NULL)
        goto t_persist;

    if (curr == '>')
    {
        p_cnt = 3;
        _peek(lexer, peek, p_cnt);

        if (strncmp(peek, ">>=", p_cnt) == 0)
        {
            strncpy(token + 1, peek, p_cnt);

            while (p_cnt--) // consuming
                _next_char(lexer, &curr);

            goto t_persist;
        }
    }

    if (curr == '<' || curr == '>' || curr == '.')
    {
        p_cnt = 2;

        _peek(lexer, peek, p_cnt);

        status = strncmp(peek, ">>", p_cnt) == 0;
        status = strncmp(peek, ">=", p_cnt) == 0 || status;
        status = strncmp(peek, "<=", p_cnt) == 0 || status;
        status = strncmp(peek, "..", p_cnt) == 0 || status;

        if (status)
        {
            strncpy(token + 1, peek, p_cnt);

            while (p_cnt--) // consuming
                _next_char(lexer, &curr);

            goto t_persist;
        }
    }

    if (strchr(mix_pt, curr) != NULL)
    {
        _peek(lexer, peek, 1);

        if (peek[0] == '=' || peek[0] == '>')
        {

            token[t_cnt++] = peek[0];

            _next_char(lexer, &curr); // consuming

            goto t_persist;
        }
        // _next_char(lexer, &curr);
    }

    if (strchr(id_pt, curr) != NULL)
    {
        _peek(lexer, peek, 1);

        if (peek[0] == curr)
        {
            token[t_cnt++] = peek[0];

            _next_char(lexer, &curr); // consuming
            goto t_persist;
        }
    }

t_persist:
    // add to array

    printf("punctuation --> %s\n", token);

t_exit:

    return RM_SUCCESS;
}

const int _identifier(rm_lexer *lexer, rm_list *tokens)
{
    int curr;  // current char
    int t_cnt; // token char count

    char token[TOK_SIZE];

    if (lexer == NULL || tokens == NULL)
        return RM_FAIL;

    curr = 0;
    t_cnt = 0;
    memset(token, 0, TOK_SIZE);

    _curr_char(lexer, &curr);

    if (isalnumundol(curr) == 0)
        return RM_FAIL;

    while (isalnumundol(curr))
    {
        token[t_cnt++] = curr;
        _next_char(lexer, &curr);
    }

    // add to token

    printf("identifier --> %s\n", token);

    return RM_SUCCESS;
}

const int _comment(rm_lexer *lexer, rm_list *tokens)
{               // might not work
    int curr;   // current char
    int status; // func. status

    if (lexer == NULL || tokens == NULL)
        return RM_FAIL;

    curr = 0;
    status = 0;

    _match(lexer, &status, '/', 0);
    _curr_char(lexer, &curr);

    if (curr == '/' && status)
        while (curr != 0 && curr != '\n')
        {
            _next_char(lexer, &curr);
        }

    return RM_SUCCESS;
}

#endif // RM_SPEC
