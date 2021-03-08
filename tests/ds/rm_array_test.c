#include <stdio.h>
#include <stdlib.h>

#include "../../src/ds/rm_array.h"

int main(){
    int a;
    rm_array * f = malloc(sizeof(rm_array));

    // rm_array_init(f, 6);

    // printf("size is %d \n", f->capacity);
    rm_array_init_fill(f, 6, 99);

    // for(a = 0; a < 7; a++){
    //     printf("%d ",(int) f->data[a]);
    // }

    rm_array_destroy(f);

    return 0;
}