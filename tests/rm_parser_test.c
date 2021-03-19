

#include <string.h>

#include "../src/parser/rm_parser.h"

int main()
{

    int src_cnt;
    rm_array a;
    char *src = "1e1f    2.f    .3f    0f    3.14f    6.022137e+23f";

    src_cnt = strlen(src);

    lexer t = {0, 0, src_cnt, src};

    language b = {{&_numeric}, "Java"};

    printf("die4guy\n");

    scan_token(&t, &b, &a);

    return 0;
}
