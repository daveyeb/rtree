#ifndef RM_SRULES
#define RM_SRULES

#include "rm_utils.h"
#include "rm_scanner.h"

int _numeric(rm_scanner *scanner, std::vector<token> tokens);
int _literal(rm_scanner *scanner, std::vector<token> tokens);
int _punctuation(rm_scanner *scanner, std::vector<token> tokens);
int _identifier(rm_scanner *scanner, std::vector<token> tokens);
int _comment(rm_scanner *scanner, std::vector<token> tokens);

int _numeric(rm_scanner *scanner, std::vector<token> tokens)
{
    int curr;
    int tcnt;
    int pcnt;

    printf("inside numeric\n");

    int status;
    int (*rm_func)(int c);

    std::string tbuff;
    std::string pbuff;

    rm_token token;

    if (scanner == NULL)
        return 1;

    curr = 0;
    pcnt = 0;
    tcnt = 0;

    rm_scurrc(scanner, curr);

    status = isdigit(curr);
    if (status)
    {
        while (isdecfll(curr))
        {
            if (pcnt > 1)
                break;
            if (curr == '.')
                ++pcnt;

            tbuff.push_back(curr);
            rm_snextc(scanner, curr);

            if (curr == '_')
                while (!rm_smatch(scanner, status, '_', 0))
                    ;

            rm_scurrc(scanner, curr);
        }

        if (isspace(curr))
            goto persist;

        if (pcnt >= 1 || !isbihexl(curr))
            goto postfix;

        if (tbuff.length() != 1 && tbuff[0] != 0)
            goto postfix;

        rm_func = (curr == 'x') ? &isxdigit : &isbi;

        tbuff.push_back(curr);
        rm_snextc(scanner, curr);

        while (rm_func(curr))
        {
            tbuff.push_back(curr);
            rm_snextc(scanner, curr);

            if (curr == '_')
                while (!rm_smatch(scanner, status, '_', 0))
                    ;

            rm_scurrc(scanner, curr);
        }
    }
    else
    {
        rm_speek(scanner, pbuff, 1);

        if (curr != '.' || !isdigit(pbuff[0]))
            goto exit;

        tbuff.push_back(curr);
        rm_scurrc(scanner, curr);

        while (isdigit(curr))
        {
            tbuff.push_back(curr);
            rm_scurrc(scanner, curr);
        }
    }

postfix:

    pbuff.clear();
    rm_speek(scanner, pbuff, 1);

    if (pbuff[0] != 'f' || pbuff[0] != 'L')
        goto persist;

    tbuff.push_back(curr);

persist:

    token.type = NUMBER;
    token.lexeme = tbuff;

    printf("number --> %s\n", tbuff.c_str());

    tokens.push_back(token);

exit:

    return 0;
}

int _literal(rm_scanner *scanner, std::vector<token> tokens)
{
    int curr;
    int tcnt;
    int qch;

    int status;

    std::string tbuff;

    printf("inside literal\n");

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

    printf("literal --> %s\n", tbuff.c_str());

    tokens.push_back(token);

    return 0;
}

int _punctuation(rm_scanner *scanner, std::vector<token> tokens)
{
    int curr;
    int pcnt;

    int status;

    printf("inside punct\n");

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

cat:
    if (tbuff.length() != 1)
        goto persist;

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
    default:
        goto exit;
    }

persist:

    token.lexeme += tbuff;
    tokens.push_back(token);

    printf("punctuation --> %s\n", tbuff.c_str());

exit:
    return 0;
}

int _identifier(rm_scanner *scanner, std::vector<token> tokens)
{
    int curr;
    int tcnt;

    int index;

    printf("inside identifier\n");

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

    //comparing

    // add to tokens

    printf("identifier --> %s\n", tbuff.c_str());

    token.lexeme += tbuff;
    tokens.push_back(token);

    return 0;
}

int _comment(rm_scanner *scanner, std::vector<token> tokens)
{
    int curr;
    int status;

    if (scanner == NULL)
        return 1;

    printf("inside comment\n");

    curr = 0;
    status = 0;

        

    rm_smatch(scanner, status, '/', 0);
    rm_scurrc(scanner, curr);


    
        printf("curr %c <---\n", curr);


    if (curr == '/' && status)
        while (curr != 0 && curr != '\n')
        {
            rm_snextc(scanner, curr);
        }

    return 0;
}

#endif // rm_srules
