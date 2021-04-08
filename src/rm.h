#ifndef RM
#define RM

#include <stdio.h>
#include <string.h>

#include "rm_utils.h"
#include "rm_srules.h"

static inline int scan_tokens(rm_scanner *scanner, std::vector<rm_token> tokens, rm_srules rules);

static inline int scan_tokens(rm_scanner *scanner, std::vector<rm_token> tokens, rm_srules rules)
{
    int adch;

    if (scanner == NULL)
        return 1;

    while (scanner->current < scanner->length)
    {
        rules._numeric(scanner, tokens);
        rules._identifier(scanner, tokens);
        rules._comment(scanner, tokens);
        rules._punctuation(scanner, tokens);
        rules._literal(scanner, tokens);

        // skip whitespaces and already consumed characters
        rm_snextc(scanner, adch);
    }

    return 0;
}

int main()
{

    // int idx;
    // int c;
    // unsigned int inlen;
    // FILE *file;
    // char buff[4906] = {0};
    std::vector<token> toks;
    std::vector<rm_srcfile> srfls;

    // file = fopen("input", "r");

    // idx = 0;
    // while (1)
    // {
    //     idx = fgetc(file);

    //     if (feof(file))
    //         break;

    //     buff[idx++] = c;
    // }
    // fclose(file);

    // inlen = strlen(buff);

    rm_open_dir(L"../src", srfls);

    rm_scanner scanner = {.srcfiles = srfls};
    rm_srules rm_sr = {_numeric, _identifier, _comment, _punctuation, _literal};

    scan_tokens(&scanner, toks, rm_sr);

    return 0;
}

#endif // rm