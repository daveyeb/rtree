#ifndef RM_UTILS
#define RM_UTILS

#include <string>
#include <vector>
#include <ctype.h>
#include <fstream>

#include "tinydir/tinydir.h"

typedef enum types
{
    // keywords.
    FROM,
    IMPORT,
    AS,
    USE,
    LOAD,
    REQUIRE,
    INCLUDE,
    // puncts.
    OPARENS = 28,
    CPARENS = 29,
    DQUOTES = 34,
    POUND = 35,
    SQUOTES = 39,
    ASTERISKS = 42,
    COMMA = 44,
    PERIOD = 46,
    FSLASH = 47,
    SEMICOLON = 59,
    LTHAN = 60,
    GTHAN = 62,
    OCBRACKS = 123,
    CCBRACKS = 125,
    PUNCT,
    // literals.
    STRING,
    NUMBER,
    LITERAL
} rm_ttypes;

typedef struct srcfile
{
    std::string ext;
    std::string name;
    std::string path;
} rm_srcfile;

typedef struct token
{
    rm_ttypes type;
    std::string lexeme;
    std::string raw;
} rm_token;

typedef struct scanner
{
    //indices.
    unsigned int start;
    unsigned int current;
    unsigned int length;
    //buffer.
    std::string sbuffer;
    //source files.
    std::vector<rm_srcfile> srcfiles;
} rm_scanner;

typedef struct parser
{
    unsigned int start;
    unsigned int current;
    unsigned int length;
    std::vector<token> tbuffer;
} rm_parser;

typedef struct srules
{
    int (&_numeric)(rm_scanner *p, std::vector<rm_token> tokens);
    int (&_identifier)(rm_scanner *p, std::vector<rm_token> tokens);
    int (&_comment)(rm_scanner *p, std::vector<rm_token> tokens);
    int (&_punctuation)(rm_scanner *p, std::vector<rm_token> tokens);
    int (&_literal)(rm_scanner *p, std::vector<rm_token> tokens);
} rm_srules;

typedef struct statement
{
    std::string file;
    std::string inc;
    std::string alias;
    int type;
} rm_statement;

typedef struct prules
{
    int (*_java)(rm_parser *p, std::vector<rm_statement> statement);
} rm_prules;

int isbi(int c);
int isalnd(int c);
int issdq(int c);

int isdecfll(int c);
int isbihexl(int c);
int strcont(std::string a, std::string b);

int istokeq(token a, token b);

int rm_open_dir(const std::wstring dirname, std::vector<rm_srcfile> &srcfiles);

int isbi(int c)
{
    return (c == 48 || c == 49);
}

int issdq(int c)
{

    return (c == 34 || c == 39);
}

int isalnd(int c)
{
    return isalnum(c) || c == 95 || c == 36;
}

int isdecfll(int curr)
{
    std::string ilch = "-+e.";

    return ilch.find(curr) == std::string::npos || isdigit(curr);
}

int isbihexl(int c)
{

    return c == 'x' || c == 'b';
}

int istokeq(token a, token b)
{
    int result;

    result = a.type == b.type;
    result = a.lexeme.compare(b.lexeme) == 0 && result;
    result = a.raw.compare(b.raw) == 0 && result;

    return result;
}

int strcont(std::string a, std::string b)
{
    return (a.find(b) != std::string::npos);
}

int rm_open_dir(const std::string dirname, std::vector<rm_srcfile> &srcfiles)
{
    tinydir_dir dir;
    tinydir_file file;

    rm_srcfile tsrcfile;

    if (dirname.length() == 0)
        return 1;

    tinydir_open(&dir, dirname.c_str());

    while (dir.has_next)
    {

        tsrcfile.ext.clear();
        tsrcfile.name.clear();
        tsrcfile.path.clear();

        tinydir_readfile(&dir, &file);

        if (file.is_dir)
        {
            if (!strcont("..", std::string(file.name)))
                rm_open_dir(std::string(file.path), srcfiles);

            tinydir_next(&dir);
            continue;
        }

        tsrcfile.ext = file.extension;
        tsrcfile.name = file.name;
        tsrcfile.path = file.path;

        srcfiles.push_back(tsrcfile);

        tinydir_next(&dir);
    }

    tinydir_close(&dir);

    // TODO: test read files on permission restrictions

    return 0;
}

int rm_read_file(rm_srcfile file, std::string &buffer)
{
    int index;
    int ch;

    FILE *fptr;

    fptr = fopen(file.path.c_str(), "r");

    if (fptr == NULL)
    {
        printf("here");
        return 1;
    }

    while (1)
    {
        ch = fgetc(fptr);

        if (feof(fptr))
            break;

        buffer += ch;
    }

    fclose(fptr);

    return 0;
}

#endif // rm_utils
