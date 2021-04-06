#ifndef RM_UTILS
#define RM_UTILS

#include <string>
#include <vector>
#include <ctype.h>

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

typedef struct token
{
    rm_ttypes type;
    std::string lexeme;
    std::string raw;
} rm_token;

typedef struct scanner
{
    unsigned int start;
    unsigned int current;
    unsigned int length;
    std::string sbuffer;
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
    int (*_numeric)(rm_scanner *p, std::vector<rm_token> tokens);
    int (*_identifier)(rm_scanner *p, std::vector<rm_token> tokens);
    int (*_comment)(rm_scanner *p, std::vector<rm_token> tokens);
    int (*_punctuation)(rm_scanner *p, std::vector<rm_token> tokens);
    int (*_literal)(rm_scanner *p, std::vector<rm_token> tokens);
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

int isbi(int c)
{
    return (c == 48 || c == 49);
}

int issdq(int c)
{

    return (c == 34 || c == 39);
}

int isalnd(char c)
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

int strcont(std::string a, std::string b){
    return (a.find(b) == std::string::npos);
}

#endif // rm_utils