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

    printf("here \n ");

    rm_open_dir(rm_str("\\Users\\M40812\\Desktop\\webpack-4336fccbbda1e5fe8437a43a3fd8f730ced056b1"), files);

    // rm_open_dir(rm_str("\\Users\\M40812\\root\\repomap-robot"), files);

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