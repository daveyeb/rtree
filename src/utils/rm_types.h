#ifndef RM_TYPES
#define RM_TYPES

#include <vector>
#include <string>
#include <map>

// types
typedef enum token_types
{
    // keywords
    FROM,
    IMPORT,
    USE,
    LOAD,
    REQUIRE,
    INCLUDE,
    // punctuations
    PUNCT,
    OPARENS = 40,
    CPARENS = 41,
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
    // literals
    LITERAL,
    STRING,
    ENDOFFILE,
} rm_tt;

typedef std::string rm_str;
typedef std::pair<rm_str, int> rm_pair;
typedef std::map<rm_str, int> rm_map;

typedef struct src_file
{
    rm_str ext;
    rm_str name;
    rm_str path;
} rm_sf;

typedef std::vector<rm_sf> rm_sfs;

typedef struct token
{
    rm_tt type;
    rm_str lexeme;
    rm_str raw;
} rm_t;

typedef struct statement
{
    rm_str file;
    std::vector<rm_str> imports;
} rm_st;

typedef std::vector<rm_t> rm_ts;
typedef std::vector<rm_st> rm_sts;

typedef struct scanner
{
    //index
    unsigned int current;
    //buffer
    rm_str buffer;
} rm_s;

typedef struct parser
{
    //indices
    unsigned int current;
    //buffer
    rm_ts buffer;
    //tokens
    rm_ts tokens;
} rm_p;

typedef struct scan_spec
{
    int (&_identifier)(rm_s *s, rm_ts &t);
    int (&_comment)(rm_s *s);
    int (&_punctuation)(rm_s *s, rm_ts &t);
    int (&_literal)(rm_s *s, rm_ts &t);
} rm_ss;

typedef struct parse_spec
{
    int (&_javascript)(rm_p *p, rm_st &st);
} rm_ps;

#endif // !RM_TYPES