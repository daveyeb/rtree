#ifndef RM_SCANNER
#define RM_SCANNER

#include "rm_utils.h"

int rm_speek(rm_scanner *scanner, std::string result, int npos);
int rm_smatch(rm_scanner *scanner, int &result, char expected, int iscase);
int rm_scurrc(rm_scanner *scanner, int &c);
int rm_snextc(rm_scanner *scanner, int &c);

int rm_speek(rm_scanner *scanner, std::string result, int npos)
{
    int blen;
    int curr;

    if (scanner == NULL)
        return 1;

    blen = scanner->sbuffer.length();
    curr = scanner->current;

    if ((curr + npos) >= blen)
        return 1;

    result = scanner->sbuffer.substr(curr, npos);

    return 0;
}

int rm_smatch(rm_scanner *scanner, int &result, char expected, int iscase)
{
    int blen;
    int curr;
    int cch;

    if (scanner == NULL || result == NULL)
        return 1;

    result = 0;
    blen = scanner->sbuffer.length();
    curr = scanner->current;
    cch = (iscase) ? toupper(scanner->sbuffer[curr]) : scanner->sbuffer[curr];

    if ((curr >= blen) || (cch != expected))
        return 1;

    result = 1;
    ++scanner->current;

    return 0;
}

int rm_scurrc(rm_scanner *scanner, int &c)
{
    int blen;
    int curr;

    if (scanner == NULL || c == NULL)
        return 1;

    blen = scanner->sbuffer.length();
    curr = scanner->current;

    if (curr < blen)
        c = scanner->sbuffer[curr];
    else
        c = 0;

    return 0;
}

int rm_snextc(rm_scanner * scanner, int &c)
{
    int blen;
    int curr;

    if (scanner == NULL || c == NULL)
        return 1;

    blen = scanner->sbuffer.length();
    curr = scanner->current;

    if (curr < blen)
        c = scanner->sbuffer[++curr];
    else
        c = 0;

    scanner->current = curr;

    return 0;
}



#endif // rm_scanner
