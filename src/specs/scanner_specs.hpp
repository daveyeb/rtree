#ifndef SCANNER_SPEC
#define SCANNER_SPEC

#include "../rm_utils.hpp"

int _literal(rm_s *scanner, rm_ts &toks)
{
    int current;
    int status;
    int qch;

    rm_str tstr;
    rm_t tok;

    if (scanner == NULL)
        return 1;

    current = 0;

    rm_s_curr(scanner, current);

    if (!issdq(current))
        return 1;

    qch = current;
    rm_s_next(scanner, current);

    while (current != qch)
    {
        if (current == 92)
        {
            tstr.push_back(current);
            rm_s_next(scanner, current);
            tstr.push_back(current);
        }
        else
        {
            tstr.push_back(current);
        }

        rm_s_next(scanner, current);
    }

    tok.type = STRING;
    tok.lexeme = tstr;
    tok.raw = rm_str("\"" + tstr + "\"");

    toks.push_back(tok);

    return 0;
}

int _punctuation(rm_s *scanner, rm_ts &toks)
{
    int current;
    int status;
    int count;

    rm_str tstr;
    rm_str pstr;
    rm_t tok;

    const rm_str pts = "<>,*;{}()#/.";

    if (scanner == NULL)
        return 1;

    rm_s_curr(scanner, current);

    if (!ispunct(current))
        return 1;

    if (issdq(current))
        return 1;

    if (!isscont(pts, rm_str(1, current)))
        return 1;

    tok.type = (rm_tt)current;
    tok.lexeme += current;

    toks.push_back(tok);

    return 0;
}

int _identifier(rm_s *scanner, rm_ts &toks)
{
    int current;
    int count;
    int index;

    rm_str tstr;
    rm_str ltstr;
    rm_t tok;

    const char *ids[] =
        {"from",
         "import",
         "use",
         "load",
         "require",
         "include"};

    if (scanner == NULL)
        return 1;

    rm_s_curr(scanner, current);

    if (!isalnd(current))
        return 1;

    while (isalnd(current))
    {
        tstr += current;
        rm_s_next(scanner, current);
    }

    tok.type = LITERAL;

    ltstr += tstr;
    rm_tolower(ltstr);

    index = -1;

    while (!isseq(ids[index + 1], ltstr))
    {

        if ((index + 1) >= 5)
        {
            index = -1;
            break;
        }
        index++;
    }

    if (index >= 0)
        tok.type = (rm_tt)++index;

    tok.lexeme += tstr;

    toks.push_back(tok);

    return 0;
}

int _comment(rm_s *scanner)
{
    int current;
    int status;

    rm_str pch;

    if (scanner == NULL)
        return 1;

    current = 0;
    status = 0;

    rm_s_match(scanner, status, '/');
    rm_s_curr(scanner, current);

    if (current == '/' && status)
        while (current != 0 && current != '\n')
            rm_s_next(scanner, current);

    if (current == '*' && status)
        while (current != 0)
        {
            rm_s_next(scanner, current);
            rm_s_peek(scanner, pch, 1);

            if (current == '*' && pch[0] == '/')
            {
                rm_s_next(scanner, current);
                rm_s_next(scanner, current);
                break;
            }
        }

    return 0;
}

#endif // !SCANNER_SPEC