#include "rm_utils.hpp"
#include "rm_scanner.hpp"
#include "rm_parser.hpp"

#include "specs/parser_specs.hpp"
#include "specs/scanner_specs.hpp"

int main()
{
    int index;
    rm_s scanner;
    rm_p parser;

    rm_sts stmts;

    rm_ss sspec =
        {
            _identifier,
            _comment,
            _punctuation,
            _literal};

    rm_ps pspec =
        {
            _javascript
        };

    rm_open_dir(rm_str("/Users/thesun/repomapp"), scanner.files);

    scan_tokens(&scanner, parser.tokens, sspec);
    scan_statement(&parser, stmts, pspec);

    index = 0;
    while(index < stmts.size()){
        printf("%d imports %s\n", index, stmts[index].imports[0].c_str());
        index++;
    }

    return 0;
}