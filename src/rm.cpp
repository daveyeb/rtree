#include "rm_utils.hpp"
#include "rm_scanner.hpp"
#include "rm_parser.hpp"

#include "specs/parser_specs.hpp"
#include "specs/scanner_specs.hpp"

void printStmts(rm_sts &stmts)
{
    int index = 0;
    while (index < stmts.size())
    {
        printf("%d file %s\n", index, stmts[index].file.c_str());
        fflush(stdin);

        int i = 0;
        while (i < stmts[index].imports.size())
        {
            printf("\t import %s \n", stmts[index].imports[i].c_str());
            fflush(stdin);
            i++;
        }

        index++;
    }
}

int main()
{

    rm_s scanner;
    rm_p parser;

    rm_st stmt;
    rm_sts stmts;
    rm_sfs files;

    rm_ss sspec =
        {
            _identifier,
            _comment,
            _regexp,
            _punctuation,
            _literal
            };

    rm_ps pspec =
        {
            _javascript};

    printf("here \n ");
    fflush(stdin);

    rm_open_dir(rm_str("\\Users\\M40812\\root\\repomap-robot\\test"), files);

    // rm_open_dir(rm_str("\\Users\\M40812\\Desktop\\freeCodeCamp-main"), files);

    rm_fforeach(files);
    printf("file %s\n\n", files.at(i).path.c_str());
    fflush(stdin);
    stmt.file = files.at(i).path.c_str();
    rm_read_file(files.at(i), scanner.buffer);
    scan_tokens(&scanner, parser.tokens, sspec);
    // scan_statement(&parser, stmt, pspec);

    stmts.push_back(stmt);
    
    rm_fforend();

    

    printStmts(stmts);

    printf("-->> done <---\n");

    return 0;
}