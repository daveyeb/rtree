#ifndef RM
#define RM

#include <stdio.h>
#include <string.h>

#include "rm_utils.h"
#include "rm_srules.h"
#include "rm_prules.h"

static inline int scan_tokens(rm_scanner *scanner, std::vector<rm_token> &tokens, rm_srules rules);
static inline int scan_stmts(rm_parser *parser, std::vector<rm_statement> &stmts, rm_prules rules);

static inline int scan_tokens(rm_scanner *scanner, std::vector<rm_token> &tokens, rm_srules rules)
{
    int adch;
    int index;

    if (scanner == NULL)
        return 1;

    index = 0;

    while (index < scanner->srcfiles.size())
    {
        scanner->current = 0;
        scanner->sbuffer.clear();

        rm_read_file(scanner->srcfiles.at(index), scanner->sbuffer);
        scanner->length = scanner->sbuffer.length();

        while (scanner->current < scanner->length)
        {
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

static inline int scan_stmts(rm_parser *parser, std::vector<rm_statement> &stmts, rm_prules rules)
{
    rm_token adtok;
    int index;

    if (parser == NULL)
        return 1;

    index = 0;
    parser->current = 0;

    while (index < parser->tokens.size())
    {
        rules._js(parser, stmts);

        index++;
    }

    return 0;
}

int main()
{

    std::vector<rm_token> toks;
    std::vector<rm_statement> stmts;
    std::vector<rm_srcfile> srfls;
    int index;

    rm_open_dir("/Users/thesun/repomap/tests", srfls);

    rm_srules rm_sr = {_identifier, _comment, _punctuation, _literal};
    rm_prules rm_pa = {_js};
    rm_scanner scanner = {};
    rm_parser parser = {};

    scanner.srcfiles = srfls;
    scan_tokens(&scanner, toks, rm_sr);

    parser.tokens = toks;
    scan_stmts(&parser, stmts, rm_pa);

    for (index = 0; index < stmts.size(); index++)
    {
        printf("statements %s\n", stmts[index].inc.c_str());
    }

    //  for(index =0; index < toks.size(); index++){

    //     printf("toks lex %s\n", toks[index].lexeme.c_str());
    // }

    return 0;
}

#endif // rm