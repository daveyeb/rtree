
#include <stdio.h>
#include <string.h>

#include "../src/rm_scanner.h"

int main()
{

    FILE *fp;
    int src_cnt;
    rm_list a;
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

    rm_lexer t = {0, 0, src_cnt, buffer};

    rm_language b = {{&_numeric, &_identifier, &_comment, &_punctuation, &_literal}, "All"};

    printf("die4guy\n\n");
    rm_list_init(&a, sizeof(rm_token));
    scan_token(&t, &a, &b);

    printf("\nlist size %zu\n", a.size);

    int m = 0;
    for(; m < a.capacity; m++){
        printf(" %d element %s\n", m, ((rm_token **)a.data)[m]->raw);

        if(m == 20) break; 
    }


    return 0;
}
