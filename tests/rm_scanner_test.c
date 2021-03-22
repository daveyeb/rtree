
#include <stdio.h>
#include <string.h>

#include "../src/rm_scanner.h"

int main()
{

    FILE *fp;
    int src_cnt;
    rm_array a;
    int c;
    int q;
    char buffer[4096] = {0};

    fp = fopen("INPUT", "r");
    q = 0;
    while (1)
    {
        c = fgetc(fp);
        if (feof(fp))
        {
            break;
        }
        buffer[q++] = c;
    }
    fclose(fp);

    src_cnt = strlen(buffer);

    lexer t = {0, 0, src_cnt, buffer};

    language b = {{&_numeric, &_identifier, &_comment, &_punctuation, &_literal}, "All"};

    printf("die4guy\n\n");

    scan_token(&t, &a, &b);

    return 0;
}
