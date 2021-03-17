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

    buf_count = 0;
    memset(&buf, 0, BUF_SIZE);

    _curr_char(lex, &cc);

    // printf("cc --> %c %d \n", cc, isdigit(cc));

    switch (isdigit(cc))
    {
    case 1:
        while (isdigit(cc) || cc == '.')
        {
            // printf("here %c\n", cc);
            buf[buf_count++] = cc;
            _next_char(lex, &cc);
        }

        if (buf_count == 1 && buf[0] == '0')
        {
            _curr_char(lex, &cc);

            switch (cc)
            {
            case 'x':
                // Consume x
                buf[buf_count++] = cc;
                _next_char(lex, &cc);

                while (isxdigit(cc))
                {
                    buf[buf_count++] = cc;
                    _next_char(lex, &cc);
                    if (cc == '_')
                        while (!_match(lex, '_', 0))
                            ;
                }

                break;
            case 'b':

                // Consume b
                buf[buf_count++] = cc;
                _next_char(lex, &cc);

                while (isbinary(cc))
                {
                    buf[buf_count++] = cc;
                    _next_char(lex, &cc);
                    if (cc == '_')
                        while (!_match(lex, '_', 0))
                            ;
                }

                if (strchr(buf, '.') != NULL)
                {
                    int found;

                    _match(lex, 'L', &found);

                    if (found)
                        buf[buf_count++] = 'L';

                    _match(lex, 'f', &found);

                    if (found)
                        buf[buf_count++] = 'f';
                }

                /// add to tokens
                printf("number --> %s \n", buf);

                break;
                // case 0:
                //     if(cc == '.'){
                //         buf[buf_count++] = cc;
                //         _next_char(lex, cc);
                //     }

                //     break;

            default:
                break;
            }
        }
        printf("number --> %s \n", buf);

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

    const char *single_punct = ";{}[]()";
    const char *mix_punct = "<>=!+-*%&|^/";
    const char *identical_punct = "+-<>&|";

    _curr_char(lex, &cc);
    // printf("here %c\n", cc);

    if (!ispunct(cc))
        return 1;
    if (cc == 34 || cc == 39)
        return 1;

    buf_count = 0;
    memset(&buf, 0, BUF_SIZE);

    printf("hrere %c \n", cc);
    if (strchr(single_punct, cc) != NULL)
    {
        // add to token

        buf[buf_count++] = cc;
        printf("punctuation --> %s \n", buf);

        return 0;
    }

    // >>>=    | 4
    if (cc == '>')
    {

        cnsm_count = 3;

        buf[buf_count++] = cc;
        _peek(lex, &buf[buf_count], cnsm_count);

        if (strncmp(buf, ">>>=", cnsm_count + 1) == 0)
        {
            // add to token
            printf("punctuation --> %s \n", buf);

            while (cnsm_count--)
                _next_char(lex, 0);
            return 1;
        }
    }

    // <<= >>= >>>   | 3
    if (cc == '<' || cc == '>')
    {
        cnsm_count = 2;

        buf[buf_count++] = cc;
        _peek(lex, &buf[buf_count], cnsm_count);

        found = strncmp(buf, ">>>", cnsm_count + 1) == 0;
        found = found || strncmp(buf, ">>=", cnsm_count + 1) == 0;
        found = found || strncmp(buf, "<<=", cnsm_count + 1) == 0;

        if (found)
        {
            // add to token
            printf("punctuation --> %s \n", buf);

            while (cnsm_count--)
                _next_char(lex, 0);
            return 1;
        }
    }

    if (strchr(mix_punct, cc) != NULL)
    {

        buf[buf_count++] = cc;
        _peek(lex, &buf[buf_count], 1);

        printf("hrere howe\n");

        if (strncmp(buf, "=", 1) == 0)
        {
            // add to token
            printf("punctuation --> %s \n", buf);

            _next_char(lex, 0);
            return 1;
        }

        return 0;
    }

    if (strchr(identical_punct, cc) != NULL)
    {

        buf[buf_count++] = cc;
        _peek(lex, &buf[buf_count], 1);

        if (buf[0] == cc)
        {
            // add to token
            printf("%s\n", buf);

            _next_char(lex, 0);
            return 1;
        }
    }

    // add to token
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