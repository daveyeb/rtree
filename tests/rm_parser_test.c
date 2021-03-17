

#include <string.h>

#include "../src/parser/rm_parser.h"
#include "../src/rules/rm_spec_java.h"

int main()
{

    int src_cnt;
    char **tokens;
    char *src = "int var  >>>= 0l    0777L    0x100000000L    2_147_483_648L    0xC0B0L ; int fish | 55;";

    src_cnt = strlen(src);

    lexer t = {0, 0, src_cnt, src};

    language b = {{&_numeric, &_literal, &_punctuation, &_identifier, &_comment}, "Java"};

    scan_token(&t, &b, tokens);

    return 0;
}
