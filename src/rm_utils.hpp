#ifndef RM_UTILS
#define RM_UTILS

#include <string>
#include <vector>
#include <ctype.h>
#include <map>

// dependacies
#include "tinydir/tinydir.h"

// supported file extensions
#define EXT                                                                    \
    {".rb",                                                                    \
     ".java",                                                                  \
     ".cpp", ".c", ".cc", ".cxx", ".inl", ".h", ".hh", ".hpp", ".hxx", ".inc", \
     ".Swift",                                                                 \
     ".js",                                                                    \
     ".py"};

// definitions
#define rm_func static inline

// utility functions
#define issdq(c) \
    (c == 34 || c == 39)

#define isalnd(c) \
    (isalnum(c) || c == 95 || c == 36)

#define isscont(a, b) \
    (rm_str(a).find(rm_str(b)) != rm_str::npos)

#define isseq(a, b) \
    (rm_str(a).compare(rm_str(b)) == 0)

#define rm_strcat(a, b) \
    (rm_str(a) + rm_str(b))

#define rm_tolower(a)         \
    int i = 0;                \
    while (i < a.length())    \
    {                         \
        a[i] = tolower(a[i]); \
        i++;                  \
    }

#define rm_fforeach(x)             \
    {                              \
        int i = 0;                 \
        while (i < x.size()) \
        {

#define rm_fforend() \
    i++;             \
    }                \
    }

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

// rm_functions

/*
    file services
        1. rm_open_dir
        2. rm_read_file
*/

rm_func int rm_open_dir(const rm_str dir, rm_sfs &files)
{
    int index;
    int found;
    int size;

    const char *ext[] = EXT;
    rm_map known_ext;

    char *text; // tiny_dir file extension
    tinydir_dir tdir;
    tinydir_file tfile;
    rm_sf cfile;

    if (dir.length() == 0)
        return 1;

    tinydir_open(&tdir, dir.c_str());

    while (tdir.has_next)
    {
        // start blank slate
        cfile.ext.clear();
        cfile.name.clear();
        cfile.path.clear();

        // read file
        tinydir_readfile(&tdir, &tfile);
        text = tfile.extension;

        if (tfile.is_dir)
        {
            if (!isscont("..", tfile.name))
                rm_open_dir(rm_str(tfile.path), files);

            tinydir_next(&tdir);
            continue;
        }

        if (rm_str(text) == "")
        {
            tinydir_next(&tdir);
            continue;
        }

        if (known_ext.find(rm_strcat(".", text)) == known_ext.end())
        {

            index = 0;
            size = sizeof(ext) / sizeof(char *);

            while (index < size)
            {
                found = 0;

                if (rm_strcat(".", text) != ext[index])
                {
                    index++;
                    continue;
                }

                found = 1;
                known_ext.insert(rm_pair(rm_strcat(".", text), found));

                cfile.ext = tfile.extension;
                cfile.name = tfile.name;
                cfile.path = tfile.path;

                files.push_back(cfile);

                if (found)
                    break;

                index++;
            }
        }
        else
        {
            if (!known_ext.find(rm_strcat(".", text))->second)
            {
                tinydir_next(&tdir);
                continue;
            }

            cfile.ext = tfile.extension;
            cfile.name = tfile.name;
            cfile.path = tfile.path;

            files.push_back(cfile);
        }

        tinydir_next(&tdir);
    }

    tinydir_close(&tdir);

    // TODO: test read files on permission restrictions

    return 0;
}

rm_func int rm_read_file(rm_sf file, rm_str &buffer)
{
    int ch;
    FILE *fptr;

    fptr = fopen(file.path.c_str(), "r");

    if (fptr == NULL)
        return 1;

    buffer.clear();

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

/*
    Scanner funcs. 
        1. rm_s_peek()
        2. rm_s_match();
        3. rm_s_curr();
        4. rm_s_next();

*/

int rm_s_peek(rm_s *scanner, rm_str &result, const int npos)
{
    int length;
    int current;

    if (scanner == NULL)
        return 1;

    length = scanner->buffer.length();
    current = scanner->current;

    if ((current + npos) >= length)
        return 1;

    result = scanner->buffer.substr(++current, npos);

    return 0;
}

int rm_s_match(rm_s *scanner, int &result, char c)
{
    int length;
    int current;
    int ch;

    if (scanner == NULL)
        return 1;

    result = 0;
    length = scanner->buffer.length();
    current = scanner->current;
    ch = scanner->buffer[current];

    if ((current >= length) || (ch != c))
        return 1;

    result = 1;
    ++scanner->current;

    return 0;
}

int rm_s_curr(rm_s *scanner, int &c)
{
    int length;
    int current;

    if (scanner == NULL)
    {
        return 1;
    }

    length = scanner->buffer.length();
    current = scanner->current;

    if (current < length)
        c = scanner->buffer[current];
    else
        c = 0;

    return 0;
}

int rm_s_next(rm_s *scanner, int &c)
{
    int length;
    unsigned int *current;

    if (scanner == NULL)
        return 1;

    length = scanner->buffer.length();
    current = &scanner->current;

    if (*current < length)
        c = scanner->buffer[++(*current)];
    else
        c = 0;

    return 0;
}

/*
    Parser functions 
        1. rm_p_match()
        2. rm_p_curr()
        3. rm_p_peek()
        4. rm_p_next()
        5. rm_p_prev()

*/

int rm_p_match(rm_p *parser, rm_tt tt, int &result)
{
    int size;
    int current;

    rm_t tok;

    if (parser == NULL)
        return 1;

    result = 0;
    size = parser->tokens.size();
    current = parser->current;
    tok = parser->tokens[current];

    if ((current >= size) || tok.type != tt)
        return 1;

    result = 1;
    ++parser->current;

    return 0;
}

int rm_p_curr(rm_p *parser, rm_t &tok)
{
    int size;
    int current;

    if (parser == NULL)
        return 1;

    size = parser->tokens.size();
    current = parser->current;

    if (current < size)
        tok = parser->tokens[current];

    return 0;
}

int rm_p_peek(rm_p *parser, rm_ts &result, int npos)
{
    int size;
    int current;
    int index;

    if (parser == NULL)
        return 1;

    size = parser->tokens.size();
    current = parser->current;
    result.clear();

    if ((current + npos) >= size)
        return 1;

    index = 0;
    while (index < npos)
    {
        result.push_back(parser->tokens[++current]);
        ++index;
    }

    return 0;
}

int rm_p_next(rm_p *parser, rm_t &tok){
    int size;
    unsigned int * current;

    if(parser == NULL)
        return 1;

    size = parser->tokens.size();
    current = &parser->current;

    if(*current < size)
        tok = parser->tokens[++(*current)];

    return 0;
}

int rm_p_prev(rm_p *parser, rm_t &tok){
    int size;
    int current;

    if(parser == NULL)
        return 1;

    size = parser->tokens.size();
    current = parser->current;

    if(current < size)
        tok = parser->tokens[--current];

    return 0;
}

#endif // !RM_UTILS