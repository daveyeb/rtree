#ifndef RM_SRULES
#define RM_SRULES

#include "rm_utils.h"
#include "rm_scanner.h"

int _literal(rm_scanner *scanner, std::vector<token> &tokens);
int _punctuation(rm_scanner *scanner, std::vector<token> &tokens);
int _identifier(rm_scanner *scanner, std::vector<token> &tokens);
int _comment(rm_scanner *scanner, std::vector<token> &tokens);

int _literal(rm_scanner *scanner, std::vector<token> &tokens)
{
    int curr;
    int tcnt;
    int qch;

    int status;

    std::string tbuff;

    rm_token token;

    while (scanner == NULL)
        return 1;

    curr = 0;
    tcnt = 0;

    rm_scurrc(scanner, curr);

    if (!issdq(curr))
        return 1;

    qch = curr;
    rm_snextc(scanner, curr);

    while (curr != qch)
    {
        if (curr == 92)
        {
            tbuff.push_back(curr);
            rm_snextc(scanner, curr);
            tbuff.push_back(curr);
        }
        else
        {
            tbuff.push_back(curr);
        }

        rm_snextc(scanner, curr);
    }

    token.type = LITERAL;
    token.lexeme = tbuff;

    token.raw += "\"";
    token.raw += tbuff;
    token.raw += "\"";

    // printf("literal --> %s\n", tbuff.c_str());

    tokens.push_back(token);

    return 0;
}

int _punctuation(rm_scanner *scanner, std::vector<token> &tokens)
{
    int curr;
    int pcnt;

    int status;

    std::string tbuff;
    std::string pbuff;

    rm_token token;

    std::string spts = ";{}[](),";
    std::string impts = "+-<>&|:";

    if (scanner == NULL)
        return 1;

    curr = 0;
    pcnt = 0;

    rm_scurrc(scanner, curr);

    if (!ispunct(curr))
        return 1;

    if (issdq(curr))
        return 1;

    tbuff.push_back(curr);

    if (spts.find(curr) != std::string::npos)
        goto persist;

    if (curr == '>')
    {
        pcnt = 3;
        rm_speek(scanner, pbuff, pcnt);

        if (pbuff.find(">>=") != std::string::npos)
        {
            tbuff += pbuff;

            while (pcnt--)
                rm_snextc(scanner, curr);

            goto persist;
        }
    }

    if (std::string("<>.").find(curr) != std::string::npos)
    {
        pcnt = 2;

        rm_speek(scanner, pbuff, pcnt);

        long long unsigned int npos = std::string::npos;

        status = pbuff.find(">>") != npos;
        status |= pbuff.find(">=") != npos;
        status |= pbuff.find("<=") != npos;
        status |= pbuff.find("..") != npos;

        if (status)
        {
            tbuff += pbuff;

            while (pcnt--)
                rm_snextc(scanner, curr);

            goto persist;
        }
    }

    if (impts.find(curr) != std::string::npos)
    {

        rm_speek(scanner, pbuff, 1);

        status = pbuff[0] == '=';
        status |= pbuff[0] == '>';
        status |= pbuff[0] == curr;

        if (status)
        {
            tbuff += pbuff[0];

            rm_snextc(scanner, curr);
            goto persist;
        }
    }

    if (tbuff.length() != 1)
        goto persist;

persist:

    switch (tbuff[0])
    {
    case LTHAN:
        token.type = LTHAN;
        break;
    case GTHAN:
        token.type = GTHAN;
        break;
    case COMMA:
        token.type = COMMA;
        break;
    case ASTERISKS:
        token.type = ASTERISKS;
        break;
    case SEMICOLON:
        token.type = SEMICOLON;
        break;
    case OCBRACKS:
        token.type = OCBRACKS;
        break;
    case CCBRACKS:
        token.type = CCBRACKS;
        break;
    case OPARENS:
        token.type = OPARENS;
        break;
    case CPARENS:
        token.type = CPARENS;
        break;
    case DQUOTES:
        token.type = DQUOTES;
        break;
    case SQUOTES:
        token.type = SQUOTES;
        break;
    case POUND:
        token.type = POUND;
        break;
    case FSLASH:
        token.type = FSLASH;
        break;
    case PERIOD:
        token.type = PERIOD;
        break;
    case EQUALS:
        token.type = EQUALS;
        break;
    default:
        goto exit;
    }

    token.lexeme += tbuff;
    tokens.push_back(token);

    // printf("punctuation --> %s\n", tbuff.c_str());

exit:
    return 0;
}

int _identifier(rm_scanner *scanner, std::vector<token> &tokens)
{
    int curr;
    int tcnt;

    int index;

    std::string tbuff;
    std::string ltbuff;

    rm_token token;

    if (scanner == NULL)
        return 1;

    curr = 0;
    tcnt = 0;

    rm_scurrc(scanner, curr);

    if (!isalnd(curr))
        return 1;

    while (isalnd(curr))
    {
        tbuff += curr;
        rm_snextc(scanner, curr);
    }

    token.type = STRING;

    // converting to lower
    index = 0;
    while (index < tbuff.length())
    {
        ltbuff += tolower(tbuff[index++]);
    }

    if (streq(ltbuff, "from"))
        token.type = FROM;

    if (streq(ltbuff, "import"))
        token.type = IMPORT;

    if (streq(ltbuff, "as"))
        token.type = AS;

    if (streq(ltbuff, "use"))
        token.type = USE;

    if (streq(ltbuff, "load"))
        token.type = LOAD;

    if (streq(ltbuff, "require"))
        token.type = REQUIRE;

    if (streq(ltbuff, "include"))
        token.type = INCLUDE;

    // add to tokens
    printf("identifier --> %d\n", token.type);

    token.lexeme += tbuff;
    tokens.push_back(token);

    return 0;
}

int _comment(rm_scanner *scanner, std::vector<token> &tokens)
{
    int curr;
    int status;

    std::string pch;

    if (scanner == NULL)
        return 1;

    curr = 0;
    status = 0;

    rm_smatch(scanner, status, '/', 0);
    rm_scurrc(scanner, curr);

    if (curr == '/' && status)
        while (curr != 0 && curr != '\n')
        {
            rm_snextc(scanner, curr);
        }

    if (curr == '*' && status)
        while (curr != 0)
        {
            rm_snextc(scanner, curr);
            rm_speek(scanner, pch, 1);

            if (curr == '*' && pch[0] == '/')
            {
                rm_snextc(scanner, curr);
                rm_snextc(scanner, curr);
                break;
            }
        }

    return 0;
}

#endif // rm_srules
