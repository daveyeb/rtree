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
    int index;

    if (scanner == NULL)
        return 1;

    index = 0;
    while (index < scanner->srcfiles.size())
    {

        scanner->current = 0;
        scanner->start = 0;
        scanner->sbuffer.clear();

        printf("file --> %s\n", scanner->srcfiles.at(index).path.c_str());

        rm_read_file(scanner->srcfiles.at(index), scanner->sbuffer);

        scanner->length = scanner->sbuffer.length();

        printf("sbuffer --> %s %d\n\n\n", scanner->sbuffer.c_str(), scanner->length);

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


        index++;

    }

    return 0;
}

int main()
{

    std::vector<token> toks;
    std::vector<rm_srcfile> srfls;

    rm_srules rm_sr = {_numeric, _identifier, _comment, _punctuation, _literal};
    rm_scanner scanner = {};

    printf("did i get here \n");

    rm_open_dir("\\Users\\M40812\\Desktop\\repomap-robot\\src", srfls);
    scanner.srcfiles = srfls;

    scan_tokens(&scanner, toks, rm_sr);

    return 0;
}

#endif // rm