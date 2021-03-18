

#include <string.h>

#include "../src/parser/rm_parser.h"

int main()
{

    int src_cnt;
    rm_array *a;
    char *src = "1e1    2.    .3    0.0    3.14    1e-9d    1e137";

    src_cnt = strlen(src);

    lexer t = {0, 0, src_cnt, src};

    language b = {{&_numeric}, "Java"};

    scan_token(&t, &b, a);

    return 0;
}
