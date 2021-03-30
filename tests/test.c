#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/rm_list.h"
#include <limits.h>

int main(){

    // int status;
    // rm_list a;
    // rm_list q;
    // int c = 5;
    // int y = 9;

    // status = rm_array_init_fill(&a, RM_INT_SIZE_CAP, 3, &c);
    // status |= rm_array_copy(&q, &a);

    // status |= rm_array_add(&a, &y);
    // status |= rm_array_insert(&a, 1, &y);
    // status |= rm_array_delete(&a, 0);
    // status |= rm_array_get(&a, 3,&c);
    // status |= rm_array_clear(&a);
    // printf("retrieved val %d\n", c);

    rm_list tmp; 
    int sorry = 5;

    rm_list_init_fill(&tmp, RM_INT_SIZE_CAP, 8, &sorry);
    _ensure_cap(&tmp, 11);





    printf("%d max\n", INT_MAX);


    int b = 0;
    for(; b < tmp.capacity; b++){
        printf(" %d element %d\n", b, *((int **)tmp.data)[b]);

        if(b == 20) break; 
    }

    printf("tmp cap %d\n", tmp.capacity);

    // status |= rm_array_destroy(&a);
    // status |= rm_array_destroy(&q);

    // printf("here is the status %d\n", status);
    return 0; 
}


    // printf("address %d\n", (int **)a.data);
    // printf("address %zu\n", a.data_size);
    // printf("address %zun", a.capacity);
    // printf("address %zu\n", a.size);
