#ifndef RM_ARRAY
#define RM_ARRAY

#include "../utils/rm_utils.h"

#define DEFAULT_CAP 10

typedef struct array
{
    void *data;
    size_t capacity;
    size_t _data_size; // total size of data
    size_t size;       // current size of data

} rm_array;

int rm_array_init(rm_array *a, const size_t elemSize);
int rm_array_init_fill(rm_array *a, const size_t elemSize, const int *value);
int rm_array_copy(rm_array *a, rm_array *b);
int rm_array_push_back(rm_array *a, const void *value);
int rm_array_insert(rm_array *a, const size_t index, const void *value);
int rm_array_delete(rm_array *a, const size_t index);
int rm_array_resize(rm_array *a, const size_t size, const void *value);
int rm_array_get(rm_array *a, const size_t index, void *value); // get value
int rm_array_clear(rm_array *a);
int rm_array_fill_zero(rm_array *a);
int rm_array_concat(rm_array *a, rm_array *b);
int rm_array_destroy(rm_array *a);

//for each macros here

int rm_array_init(rm_array *a, const size_t elemSize)
{
    if (elemSize < 0)
        return 1;

    if (elemSize >= DEFAULT_CAP)
        a->capacity = DEFAULT_CAP * 2;
    else
        a->capacity = DEFAULT_CAP;

    a->data = malloc(elemSize);
    a->size = 0;

    return 0;
}

int rm_array_init_fill(rm_array *a, const size_t elemSize, const int *value)
{
    int status;
    status = rm_array_init(a, elemSize);

    if (status)
        return status;
    else
        memset(a->data, value, elemSize);

    return 0;
}

int rm_array_destroy(rm_array *a)
{
    if (a == NULL)
        return 0;

    free(a->data);

    free(a);

    return 0;
}

int rm_array_push_back(rm_array *a, const void *value)
{
    if (a == NULL)
        return 1;

    if (a->size + 1 >= a->capacity) // resize
        return 1;

    // memmove(a->data[a->size++], value, sizeof);

    a++;

    return 0;
}

#endif // RM_ARRAY