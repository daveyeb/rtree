#include "rm_utils.hpp"
#include "rm_scanner.hpp"
#include "rm_parser.hpp"

#include "specs/parser_specs.hpp"
#include "specs/scanner_specs.hpp"

int main()
{
    int index;

    rm_ts * tokens;
    rm_str * file;
    rm_str * buffer;
    
    rm_s scanner;
    rm_p parser;

    rm_sfs files;

    rm_st stmt;
    rm_sts stmts;

    rm_ss sspec =
        {
            _identifier,
            _comment,
            _punctuation,
            _literal
        };

    rm_ps pspec =
        {
            _javascript
        };
    
    file = &stmt.file;
    buffer = &scanner.buffer;
    tokens = &parser.tokens;

    rm_open_dir(rm_str("/Users/thesun/repomapp"), files);

    rm_fforeach(files);
    
    *file = files[i].path.c_str();
    rm_read_file(files[i], *buffer);
    scan_tokens(&scanner, *tokens, sspec);
    scan_statement(&parser, stmt, pspec);
    
    stmts.push_back(stmt);

    rm_fforend();

    index = 0;
    while (index < stmts.size())
    {
        printf("%d imports %s\n", index, stmts[index].imports[0].c_str());
        index++;
    }

    return 0;
}