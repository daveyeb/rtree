#ifndef RM_ARRAY
#define RM_ARRAY

#define RM_DEFAULT_CAP 10
#define RM_STRING_SIZE_CAP 256
#define RM_INT_SIZE_CAP 4

#define RM_SUCCESS 0
#define RM_FAIL 1

typedef struct array
{
    void **data;
    size_t data_size;
    size_t capacity;
    size_t size;

} rm_array;

int rm_array_init(rm_array *a, const size_t data_size, const size_t size);
int rm_array_init_fill(rm_array *a, const size_t data_size, const size_t size, const void *c);
int rm_array_copy(rm_array *a, rm_array *b);
int rm_array_push_back(rm_array *a, const void *value);
int rm_array_insert(rm_array *a, const size_t index, const void *value);
int rm_array_delete(rm_array *a, const size_t index);
int rm_array_get(rm_array *a, const size_t index, void *value); // get value
int rm_array_clear(rm_array *a);
int rm_array_destroy(rm_array *a);

// TODO : for each macro

int rm_array_init(rm_array *a, const size_t data_size, const size_t size)
{
    int index;

    if (data_size < 0)
        return RM_FAIL;

    index = 0;

    a->capacity = (size >= RM_DEFAULT_CAP) ? RM_DEFAULT_CAP * 2 : RM_DEFAULT_CAP;
    a->size = 0;
    a->data = calloc(a->capacity, sizeof(*a->data));
    a->data_size = data_size;

    while (index < size)
    {
        (a->data)[index] = malloc(data_size);

        index++;
        a->size++;
    }

    return RM_SUCCESS;
}

int rm_array_init_fill(rm_array *a, const size_t data_size, const size_t size, const void *c)
{
    int status;
    int index;

    status = rm_array_init(a, data_size, size);

    if (status)
        return status;

    index = 0;

    while (index < size)
    {
        memcpy((a->data)[index], c, sizeof(a->data_size));
        index++;
    }

    return RM_SUCCESS;
}

int rm_array_destroy(rm_array *a)
{
    int index;
    if (a == NULL)
        return RM_SUCCESS;

    index = 0;

    while (index < a->data_size)
    {
        free((a->data)[index]);
        index++;
    }

    free(a->data);
    free(a);

    return RM_SUCCESS;
}

int rm_array_push_back(rm_array *a, const void *value)
{
    if (a == NULL)
        return RM_FAIL;

    if (a->size + 1 >= a->capacity)
        return RM_FAIL;

    memcpy((a->data)[a->size], value, a->data_size);

    a->size++;

    // TODO: implement a resize functionality.

    return RM_SUCCESS;
}

int rm_array_insert(rm_array *a, const size_t index, const void *value)
{

    if (a == NULL)
        return RM_FAIL;

    if (index >= a->capacity)
        return RM_FAIL;

    memcpy((a->data)[index], value, a->data_size);

    return RM_SUCCESS;
}

// int rm_array_delete(rm_array *a, const size_t index)
// {
//     int status;
//     int rm_cnt[2] = {0};
//     void *tmp_data_cpy;

//     if (a == NULL)
//         return 1;

//     if (index < 0 || index >= a->capacity)
//         return 1;

//     tmp_data_cpy = (void *)malloc(sizeof(void *));
//     memcpy(tmp_data_cpy, a->data, sizeof(void *));

//     while (rm_cnt[0] <= a->size)
//     {
//         if (rm_cnt[0] == index)
//         {
//             rm_cnt[0]++;
//             continue;
//         }

//         memcpy(((int *)tmp_data_cpy) + rm_cnt[1], (a->data) + rm_cnt[0], (rm_cnt[0] + 1) * a->data_size);

//         rm_cnt[1]++;
//         rm_cnt[0]++;
//     }

//     a->size -= 1;
//     // a->capacity = new_a->capacity; // resize if less

//     memcpy(a->data, tmp_data_cpy, sizeof(void *));
//     free(tmp_data_cpy);

//     return 0;
// }

int rm_array_get(rm_array *a, const size_t index, void *value)
{

    if (a == NULL)
        return RM_FAIL;

    if (index < 0 || index >= a->capacity)
        return RM_FAIL;

    memcpy(value, (a->data)[index], sizeof(void *));

    return RM_SUCCESS;
}

int rm_array_clear(rm_array *a)
{
    int index;

    if (a == NULL)
        return RM_FAIL;

    index = 0;
    while (index < a->size)
        memset((a->data)[index++], 0, a->capacity);

    return RM_SUCCESS;
}

#endif // RM_ARRAY