#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../src/ds/rm_array.h"

int main()
{

    int status = -1;
    int index = -1;

    int b = 5;  // TODO: i dont like this, passing an integer by reference
    int * a = &b;

    rm_array * david;
    david = malloc(sizeof(rm_array));

    status = rm_array_init(david, RM_INT_SIZE_CAP, 3);
    status = rm_array_push_back(david, &index);
    status = rm_array_push_back(david, &status);
    // status = rm_array_push_back(david, &status);
    // status = rm_array_push_back(david, &index);
    status = rm_array_insert(david, 1, a);
    status = rm_array_delete(david, 3);
    status = rm_array_get(david, 0, a);

    status = rm_array_clear(david);
    
    printf("status = %d \n", *a);

    // printf("---------\n");
    for(index = 0; index < david->capacity; index++)
    {

        printf("%d ", index );
        printf("%d \n", ((int *)david->data)[index]);
    }


    // printf("\n\n size %lu\n", david->size);
    

    status = rm_array_destroy(david);


    // TODO: research can pointers overflow 
    

    return 0;
}