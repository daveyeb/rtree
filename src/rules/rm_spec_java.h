#ifndef RM_SPEC_JAVA
#define RM_SPEC_JAVA

#include "../utils/rm_utils.h"

#define BUF_SIZE 4906

static inline int _numeric(lexer *lex, char **tokens);
static inline int _literal(lexer *lex, char **tokens);
static inline int _punctuation(lexer *lex, char **tokens);
static inline int _identifier(lexer *lex, char **tokens);
static inline int _comment(lexer *lex, char **tokens);

static inline int _numeric(lexer *lex, char **tokens)
{
    int cc; // current char
    int buf_count;
    char buf[BUF_SIZE];
    char *peek_buf;
    int period_cnt;

    period_cnt = 0;
    buf_count = 0;
    memset(&buf, 0, BUF_SIZE);

    _curr_char(lex, &cc);

    switch (isdigit(cc))
    {
    case 1:
        while (isdigit(cc) || cc == '.')
        {
            if (cc == '.')
                period_cnt++;
            if (period_cnt > 1)
                break;

            buf[buf_count++] = cc;
            _next_char(lex, &cc);

            if (cc == '_')
                while (!_match(lex, '_', (int *)&peek_buf[0]))
                    ;

            _curr_char(lex, &cc);
        }

        _curr_char(lex, &cc);

        if (cc != ' ' && period_cnt >= 1)
        {
            // printf("here %s\n", buf);

            int found;
            _match(lex, 'f', &found);

            _curr_char(lex, &cc);

            if (found)
            {
                buf[buf_count++] = 'f';
            }
        }

        if (buf_count == 1 && buf[0] == '0')
        {
            _curr_char(lex, &cc);

            if (cc == 'x')
            {

                // sume x or b
                buf[buf_count++] = cc;
                _next_char(lex, &cc);

                while (isxdigit(cc))
                {
                    buf[buf_count++] = cc;
                    _next_char(lex, &cc);
                    if (cc == '_')
                        while (!_match(lex, '_', (int *)&peek_buf[0]))
                            ;
                    _curr_char(lex, &cc);
                }
            }
            else if (cc == 'b')
            {

                // sume x or b
                buf[buf_count++] = cc;
                _next_char(lex, &cc);

                while (isbinary(cc))
                {
                    buf[buf_count++] = cc;
                    _next_char(lex, &cc);
                    if (cc == '_')
                        while (!_match(lex, '_', (int *)&peek_buf[0]))
                            ;
                    _curr_char(lex, &cc);
                }
            }

            int found;

            _match(lex, 'L', &found);

            if (found || (buf_count > 1 && cc == 'L'))
            {
                buf[buf_count++] = 'L';
            }

            return 0;
        }

        int found;

        _match(lex, 'L', &found);


        if (found || (buf_count > 1 && cc == 'L'))
        {
            buf[buf_count++] = 'L';
        }

        printf("number --> %s \n", buf);

    case 0:
        memset(peek_buf, 0, 3);
        _peek(lex, peek_buf, 1);

        if (cc == '.' && isdigit(peek_buf[0]))
        {

            buf[buf_count++] = cc;
            _next_char(lex, &cc); // consume
            cc = peek_buf[0];
            while (isdigit(cc))
            {
                buf[buf_count++] = cc;
                _next_char(lex, &cc);
            }

            printf("number --> %s \n", buf);
        }

        break;

    default:
        break;
    }

    return 0;
}

static inline int _literal(lexer *lex, char **tokens)
{
    int quotation_mark;
    int cc;
    int found;
    int buf_count;
    char buf[BUF_SIZE];

    buf_count = 0;
    _curr_char(lex, &quotation_mark);

    if (quotation_mark != 34 && quotation_mark != 39)
        return 1;

    _match(lex, quotation_mark, 0); // consume " or '

    _curr_char(lex, &cc);

    while (cc != quotation_mark)
    {
        _next_char(lex, &cc);

        if (cc == 92)
        { // Consuming escape characters
            buf[buf_count++] = cc;

            _next_char(lex, &cc);

            buf[buf_count++] = cc;
        }
        else
        {
            buf[buf_count++] = cc;
            _next_char(lex, &cc);
        }
    }

    /// add to tokens
    printf("literal --> %s \n", buf);

    return 0;
}

static inline int _punctuation(lexer *lex, char **tokens)
{

    int cc;
    int found;
    int buf_count;
    int cnsm_count;
    char buf[BUF_SIZE];
    char *peek_buf;

    const char *single_punct = ";{}[]()";
    const char *mix_punct = "<>=!+-*%&|^/";
    const char *identical_punct = "+-<>&|";

    _curr_char(lex, &cc);

    if (!ispunct(cc))
        return 1;
    if (cc == 34 || cc == 39)
        return 1;

    buf_count = 0;
    memset(&buf, 0, BUF_SIZE);

    buf[buf_count++] = cc;

    if (strchr(single_punct, cc) != NULL)
    {
        // add to token -- already added

        printf("punctuation --> %s \n", buf);

        return 0;
    }

    // >>>=    | 4
    if (cc == '>')
    {

        cnsm_count = 3;

        memset(peek_buf, 0, 3);
        _peek(lex, peek_buf, cnsm_count);

        if (strncmp(peek_buf, ">>=", cnsm_count) == 0)
        {
            // add to token
            strncpy(buf + 1, peek_buf, cnsm_count);
            printf("punctuation --> %s \n", buf);

            while (cnsm_count--) // consuming
                _next_char(lex, &cc);
            return 1;
        }
    }

    // <<= >>= >>>   | 3
    if (cc == '<' || cc == '>')
    {
        cnsm_count = 2;

        memset(peek_buf, 0, 2);
        _peek(lex, peek_buf, cnsm_count);

        found = strncmp(peek_buf, ">>", cnsm_count) == 0;
        found = found || strncmp(peek_buf, ">=", cnsm_count) == 0;
        found = found || strncmp(peek_buf, "<=", cnsm_count) == 0;

        if (found)
        {
            // add to token
            strncpy(buf + 1, peek_buf, cnsm_count);
            printf("punctuation --> %s \n", buf);

            while (cnsm_count--)
                _next_char(lex, &cc);
            return 1;
        }
    }

    if (strchr(mix_punct, cc) != NULL)
    {

        _peek(lex, peek_buf, 1);

        if (peek_buf[0] == '=')
        {
            // add to token
            buf[buf_count++] = peek_buf[0];
            printf("punctuation --> %s \n", buf);

            _next_char(lex, &cc); // consume
            return 1;
        }
    }

    if (strchr(identical_punct, cc) != NULL)
    {

        _peek(lex, peek_buf, 1);

        if (peek_buf[0] == cc)
        {

            // add to token
            buf[buf_count++] = peek_buf[0];
            printf("punctuation --> %s \n", buf);

            _next_char(lex, &cc); // consume
            return 1;
        }
    }

    printf("punctuation --> %s \n", buf);

    return 0;
}

static inline int _identifier(lexer *lex, char **tokens)
{
    int cc;
    int buf_count;
    char buf[BUF_SIZE];

    _curr_char(lex, &cc);

    if (!isalnumundol(cc))
        return 1;

    buf_count = 0;

    while (isalnumundol(cc))
    {
        buf[buf_count++] = cc;
        _next_char(lex, &cc);
    }

    // add to token
    printf("identifier --> %s\n", buf);
    return 0;
}

static inline int _comment(lexer *lex, char **tokens)
{
    int cc;
    int found;

    _curr_char(lex, &cc);

    _match(lex, '/', &found);

    if (cc == '/' && found)
        while (cc != '\n')
            _next_char(lex, &cc);

    return 0;
}

#endif // RM_SPEC_JAVA
