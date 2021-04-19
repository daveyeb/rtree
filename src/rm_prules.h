#ifndef RM_PRULES
#define RM_PRULES

#include "rm_utils.h"
#include "rm_parser.h"

int _imports_java(rm_parser *parser, std::vector<rm_statement> statements);
int _imports_ccpp(rm_parser *parser, std::vector<rm_statement> statements);
int _imports_python(rm_parser *parser, std::vector<rm_statement> statements);
int _js(rm_parser *parser, std::vector<rm_statement> &stmts);
int _imports_ruby(rm_parser *parser, std::vector<rm_statement> statements);
int _imports_swift(rm_parser *parser, std::vector<rm_statement> statements);

int _imports_java(rm_parser *parser, std::vector<rm_statement> statements)
{
    int pcnt;

    token tok;
    rm_statement rms;

    if (parser == NULL)
        return 1;

    pcnt = 0;

    rm_pcurrt(parser, tok);

    if (tok.type == IMPORT)
    {
        rm_pnextt(parser, tok); // consume

        while (tok.type != SEMICOLON)
        {
            if (pcnt == 0 && strcont(tok.lexeme, "static"))
            {
                pcnt++;
                rm_pnextt(parser, tok); // skip
            }

            rms.inc += tok.lexeme;
            rm_pnextt(parser, tok); // consume
        }

        rm_pnextt(parser, tok); // consume
    }

    // string manipulation before persist
    statements.push_back(rms);

    return 0;
}

int _imports_ccpp(rm_parser *parser, std::vector<rm_statement> statements)
{
    int pcnt;
    token tok;
    rm_statement rms;

    std::vector<token> toks;

    if (parser == NULL)
        return 1;

    pcnt = 0;

    rm_ppeek(parser, toks, 2);

    if (toks[0].type == POUND && toks[1].type == INCLUDE)
    {
        rm_pnextt(parser, tok); // consume #
        rm_pnextt(parser, tok); // consume include

        rm_pnextt(parser, tok); // point to curr

        if (tok.type != STRING)
            rms.inc += tok.lexeme;
        else
            rms.inc += tok.raw;

        rm_pnextt(parser, tok); // consume
    }

    statements.push_back(rms);

    return 0;
}

int _imports_python(rm_parser *parser, std::vector<rm_statement> statements)
{
    int pcnt;

    token tok;
    std::vector<token> toks;
    rm_statement rms;

    if (parser == NULL)
        return 1;

    pcnt = 0;

    // Research more on imports typically the relative and absolute

    rm_pcurrt(parser, tok);

    switch (tok.type)
    {
    case FROM:
        /* code */

        rm_pnextt(parser, tok); // consume

        while (tok.type != IMPORT)
        {
            rms.inc += tok.lexeme;
            rm_pnextt(parser, tok); // consume
        }

        rm_pnextt(parser, tok); // consume import

        rms.alias += tok.lexeme;

        break;

    case IMPORT:
        /* code */

        rm_pnextt(parser, tok); // consume

        while (tok.type != LITERAL)
        {
            rms.inc += tok.lexeme;
            rm_pnextt(parser, tok); // consume
        }

        if (tok.type != AS)
            break;

        rms.alias += tok.lexeme;

        break;

    default:
        break;
    }

    rm_pnextt(parser, tok); // consume

    statements.push_back(rms);

    return 0;
}

int _js(rm_parser *parser, std::vector<rm_statement> &stmts)
{
    int pcnt;

    rm_token tok;
    rm_statement stmt;
    std::vector<token> toks;

    if (parser == NULL)
        return 1;

    pcnt = 0;

    rm_pcurrt(parser, tok);

    if (tok.type != IMPORT)
        return 1;

    rm_pnextt(parser, tok); // consume

    while (tok.type != SEMICOLON)
    {

        switch (tok.type)
        {

        case FROM:
            rm_pnextt(parser, tok); // consume
            stmt.inc += tok.lexeme;
            break;
        case OPARENS:
            rm_pnextt(parser, tok); // consume
            stmt.inc += tok.lexeme;
            rm_pnextt(parser, tok); // consume stmts
            break;

        default:
            break;
        }

        rm_ppeek(parser, toks, 1);
        if (toks[0].type == SEMICOLON)
        {
            printf("sus %d %s %s\n", toks[0].type, tok.lexeme.c_str(), toks[1].lexeme.c_str());
        }

        rm_pnextt(parser, tok); // consume
    }

    rm_pnextt(parser, tok); // consume

    printf("file includes %s \n", stmt.inc.c_str());
    stmts.push_back(stmt);

    return 0;
}

int _imports_ruby(rm_parser *parser, std::vector<rm_statement> statements)
{
    int status;

    token tok;
    std::vector<token> toks;
    rm_statement rms;

    if (parser == NULL)
        return 1;

    rm_pcurrt(parser, tok);

    status = tok.type != LOAD;
    status = tok.type != REQUIRE && status;
    status = tok.type != INCLUDE && status;

    if (status)
        return 1;

    rm_pnextt(parser, tok); // consume

    if (tok.type == INCLUDE)
        rms.inc += tok.lexeme;
    else
        rms.inc += tok.raw;

    rm_pnextt(parser, tok); // consume

    statements.push_back(rms);

    return 0;
}

int _imports_swift(rm_parser *parser, std::vector<rm_statement> statements)
{
    int pcnt;

    token tok;
    std::vector<token> toks;
    rm_statement rms;

    if (parser == NULL)
        return 1;

    pcnt = 0;

    rm_pcurrt(parser, tok);

    if (tok.type != IMPORT)
        return 1;

    rm_pnextt(parser, tok); // consume

    if (!isupper(tok.lexeme[0]))
        rm_pnextt(parser, tok); // consume kind

    rms.inc += tok.lexeme;
    rm_pnextt(parser, tok); // consume

    while (tok.type != PERIOD)
    {
        rms.inc += tok.lexeme;
        rm_pnextt(parser, tok); // consume
        pcnt = 1;
    }

    if (pcnt)
        rms.inc += tok.lexeme; // persist after period

    rm_pnextt(parser, tok); // consume

    statements.push_back(rms);

    return 0;
}

#endif // rm_prules