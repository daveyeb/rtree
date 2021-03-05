#ifndef RM_ARRAY
#define RM_ARRAY

#include "../utils/rm_utils.h"

typedef struct array
{
    void *data;
    size_t capacity;

} rm_array;

int rm_array_init(rm_array *a, const size_t elemSize);
int rm_array_init_fill(rm_array *a, const size_t elemSize, const int *value);
int rm_array_copy(rm_array *a, rm_array *b);
int rm_array_push_back(rm_array *a, const int *value);
int rm_array_insert(rm_array *a, const size_t index, const void * value);
int rm_array_delete(rm_array *a, const size_t index);
int rm_array_resize(rm_array *a, const size_t size, const void * value);
int rm_array_get(rm_array *a, const size_t index, void * value); // get value
int rm_array_clear(rm_array *a);
int rm_array_fill_zero(rm_array *a);
int rm_array_concat(rm_array *a, rm_array *b);
int rm_array_destroy(rm_array *a);

//for each macros here

#endif // RM_ARRAY