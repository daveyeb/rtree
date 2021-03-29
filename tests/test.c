#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/rm_array.h"


int main(){

    rm_array a;
    int c = 5;

    rm_array_init_fill(&a, RM_INT_SIZE_CAP, 3, &c);

    printf("address %d\n", (int **)a.data);
    printf("address %zu\n", a.data_size);
    printf("address %zun", a.capacity);
    printf("address %zu\n", a.size);



    int b = 0;
    for(b; b < a.size; b++){
        printf("--------\n");
        printf("love %zu\n", * ((int **)a.data)[b]);

        printf("total size of %d\n\n", sizeof(((int **)a.data)[b]));
    }


}