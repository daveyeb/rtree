#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#include "../src/rm_utils.h"

int main(){

    void * test;

    rm_token tmp;

    snprintf(tmp.value,6, "David");


    tmp.type = 9;


    test = (rm_token *) malloc(sizeof(rm_token));

    memcpy(test, &tmp, sizeof(tmp));

    // ((rm_token *)test)->type;

    printf("please let the be light %s\n", ((rm_token *)test)->raw);
    

    return 0;
}
