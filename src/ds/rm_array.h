#ifndef RM_ARRAY
#define RM_ARRAY

#include "../utils/rm_utils.h"

#define RM_DEFAULT_CAP 10
#define RM_STRING_SIZE_CAP 256
#define RM_INT_SIZE_CAP 4

typedef struct array
{
    void *data;       // 40 or 1024
    size_t data_size; // 4 or 256
    size_t capacity;  // 10
    size_t size;      // 0

} rm_array;

int rm_array_init(rm_array *a, const size_t data_size, const size_t size);
int rm_array_init_fill(rm_array *a, const size_t data_size, const size_t size, const int c);
int rm_array_copy(rm_array *a, rm_array *b);
int rm_array_push_back(rm_array *a, const void *value);
int rm_array_insert(rm_array *a, const size_t index, const void *value);
int rm_array_delete(rm_array *a, const size_t index);
// int rm_array_resize(rm_array *a, const size_t size, const void *value);
int rm_array_get(rm_array *a, const size_t index, void *value); // get value
int rm_array_clear(rm_array *a);
int rm_array_fill_zero(rm_array *a);
int rm_array_concat(rm_array *a, rm_array *b, rm_array *result);
int rm_array_destroy(rm_array *a);

//for each macros here

int rm_array_init(rm_array *a, const size_t data_size, const size_t size)
{
    if (data_size < 0)
        return 1;

    a->capacity = (size >= RM_DEFAULT_CAP) ? RM_DEFAULT_CAP * 2 : RM_DEFAULT_CAP;
    a->data = calloc(a->capacity, data_size);
    a->data_size = data_size;
    a->size = 0;

    return 0;

    // TODO: I do not understand how calloc works a
}

int rm_array_init_fill(rm_array *a, const size_t data_size, const size_t size, const int c)
{
    int status;
    int index;

    status = rm_array_init(a, data_size, size);

    if (status)
        return status;

    switch (data_size)
    {
    case RM_STRING_SIZE_CAP:

        index = 0;

        while (index < size)
        {
            memset(&((char *)a->data)[index * a->data_size], c, a->data_size - 1);

            index++;
            a->size++;
        }

        break;
    case RM_INT_SIZE_CAP:

        index = 0;

        while (index < size)
        {
            ((int *)a->data)[index] = c;

            index++;
            a->size++;
        }

        break;
    default:
        rm_array_destroy(a);

        return 1;
    }

    //TODO: improve function to only fill size argument and not the entire cap
    // 2. research going beyond int or char pointer

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

    switch (a->data_size)
    {
    case RM_STRING_SIZE_CAP:

        memcpy(&((char *)a->data)[a->size * a->data_size], value, a->data_size);

        break;
    case RM_INT_SIZE_CAP:

        memcpy(&((int *)a->data)[a->size], value, a->data_size);

        break;
    default:
        return 1;
    }

    a->size++;

    return 0;
}

int rm_array_insert(rm_array *a, const size_t index, const void *value)
{

    if (a == NULL)
        return 1;

    if (index >= a->capacity)
        return 1;

    switch (a->data_size)
    {
    case RM_STRING_SIZE_CAP:

        memcpy(&((char *)a->data)[index * a->data_size], value, a->data_size);
        break;
    case RM_INT_SIZE_CAP:

        memcpy(&((int *)a->data)[index], value, a->data_size);
        break;
    default:
        break;
    }

    return 0;
}

int rm_array_delete(rm_array *a, const size_t index)
{
    int status;
    int rm_cnt[2] = {0};
    void *tmp_data_cpy;

    tmp_data_cpy = (void *)malloc(sizeof(void *));
    memcpy(tmp_data_cpy, a->data, sizeof(void *));

    if (a == NULL)
        return 1;

    if (index >= a->capacity)
        return 1;

    while (rm_cnt[0] <= a->size)
    {
        if (rm_cnt[0] == index)
        {
            rm_cnt[0]++;
            continue;
        }

        switch (a->data_size)
        {
        case RM_STRING_SIZE_CAP:
            
            memcpy(((char *)tmp_data_cpy) + rm_cnt[1], ((char *)a->data) + rm_cnt[0], (rm_cnt[0] + 1) * a->data_size);
            
            break;

        case RM_INT_SIZE_CAP:
            
            memcpy(((int *)tmp_data_cpy) + rm_cnt[1], ((int *)a->data) + rm_cnt[0], (rm_cnt[0] + 1) * a->data_size);

            break;
        
        default:
            break;
        }

        rm_cnt[1]++;
        rm_cnt[0]++;
    }

    a->size -= 1;
    // a->capacity = new_a->capacity; // resize if less

    memcpy(a->data, tmp_data_cpy, sizeof(void *));
    free(tmp_data_cpy);

    return 0;
}

#endif // RM_ARRAY