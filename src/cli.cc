#include "rm_utils.h"
#include "rm_scanner.h"
#include "rm_parser.h"
#include "rm_file_svc.h"

#include "parser_specs.h"
#include "scanner_specs.h"

void printStmts(rm_sts &stmts)
{
    int index = 0;
    while (index < stmts.size())
    {
        printf("%d file %s\n", index, stmts[index].file.c_str());

        int i = 0;
        while (i < stmts[index].imports.size())
        {
            printf("\t import %s \n", stmts[index].imports[i].c_str());
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
            _punctuation,
            _literal};

    rm_ps pspec =
        {
            _javascript};

    rm_open_dir(rm_str("/Users/thesun/Downloads/vscode"), files);

    rm_fforeach(files);
    printf("file %s\n\n", files[i].path.c_str());
    stmt.file = files[i].path.c_str();
    rm_read_file(files[i], scanner.buffer);
    scan_tokens(&scanner, parser.tokens, sspec);
    scan_statement(&parser, stmt, pspec);
    stmts.push_back(stmt);
    rm_fforend();

    printStmts(stmts);

    return 0;
}