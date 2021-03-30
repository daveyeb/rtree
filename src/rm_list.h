#ifndef RM_LIST
#define RM_LIST

#include <limits.h>

#define RM_DEFAULT_CAP 10
#define RM_STRING_SIZE_CAP 256
#define RM_INT_SIZE_CAP 4
#define RM_MAX_CAP 10000

#define RM_SUCCESS 0
#define RM_FAIL 1

typedef struct list
{
    void **data;
    size_t data_size;
    size_t capacity;
    size_t size;

} rm_list;

int rm_list_init(rm_list *array, const size_t data_size);
int rm_list_init_fill(rm_list *array, const size_t data_size, const size_t size, const void *c);
int rm_list_copy(rm_list *src, rm_list *dest);
int rm_list_add(rm_list *array, const void *value);
int rm_list_insert(rm_list *array, const size_t index, const void *value);
int rm_list_delete(rm_list *array, const size_t index);
int rm_list_get(rm_list *array, const size_t index, void *value); 
int rm_list_clear(rm_list *array);
int rm_list_destroy(rm_list *array);

int _ensure_cap(rm_list *array, const size_t min_cap);
int _grow(rm_list *array, const size_t min_cap);
int _huge_cap(const size_t min_cap, int *new_cap);
int _copy_of(rm_list *old, const size_t size);

// TODO : for each macro

int _ensure_cap(rm_list *array, const size_t min_cap)
{
    // investigate modcount

    if (min_cap - array->capacity > 0)
        _grow(array, min_cap);

    return RM_SUCCESS;
}

int _grow(rm_list *array, const size_t min_cap)
{
    size_t old_cap = array->capacity;
    int new_cap = old_cap + (old_cap >> 1);

    if (new_cap - min_cap < 0)
        new_cap = min_cap;

    if ((new_cap - RM_MAX_CAP) > 0)
        _huge_cap(min_cap, &new_cap);

    // copy arrays
    _copy_of(array, new_cap);

    return RM_SUCCESS;
}

int _huge_cap(const size_t min_cap, int *new_cap)
{
    if (min_cap < 0)
        return RM_FAIL;

    *new_cap = (min_cap > RM_MAX_CAP) ? INT_MAX : RM_MAX_CAP;

    return RM_SUCCESS;
}

int _copy_of(rm_list *old, const size_t size)
{
    int index;
    void **out;

    if (size < 0)
        return RM_FAIL;

    index = 0;

    // allocating new array
    out = calloc(size, sizeof(*out));

    while (index < size)
    {
        out[index] = calloc(1, old->data_size);

        index++;
    }

    // copy old data to new

    index = 0;
    while (index < old->capacity)
    {
        memcpy(out[index], old->data[index], old->data_size);

        index++;
    }

    // freeing old data

    index = 0;
    while (index < old->capacity)
    {
        free(old->data[index]);

        index++;
    }
    free(old->data);

    // replace old data with new

    old->data = out;
    old->capacity = size;

    return RM_SUCCESS;
}

int rm_list_init(rm_list *array, const size_t data_size)
{
    int index;

    if (data_size < 0)
        return RM_FAIL;

    index = 0;

    array->size = 0;
    array->capacity = RM_DEFAULT_CAP;
    array->data = calloc(array->capacity, sizeof(*array->data));
    array->data_size = data_size;

    while (index < array->capacity)
    {
        (array->data)[index] = calloc(1, data_size);

        index++;
    }

    return RM_SUCCESS;
}

int rm_list_init_fill(rm_list *array, const size_t data_size, const size_t size, const void *c)
{
    int status;
    int index;

    status = rm_list_init(array, data_size);

    if (status)
        return status;

    index = 0;

    _ensure_cap(array, size);

    while (index < size)
    {
        memcpy((array->data)[index], c, array->data_size);

        array->size++;
        index++;
    }

    return RM_SUCCESS;
}

int rm_list_copy(rm_list *dest, rm_list *src)
{
    int index;

    if (src == NULL)
        return RM_FAIL;

    index = 0;
    rm_list_init(dest, src->data_size);

    while (index < src->capacity)
    {
        memcpy(dest->data[index], src->data[index], src->data_size);
        index++;
    }

    dest->size = src->size;

    return RM_SUCCESS;
}

int rm_list_destroy(rm_list *array)
{
    int index;
    if (array == NULL)
        return RM_SUCCESS;

    index = 0;

    while (index < array->data_size)
    {
        free((array->data)[index]);
        index++;
    }

    free(array->data);

    return RM_SUCCESS;
}

int rm_list_add(rm_list *array, const void *value)
{
    if (array == NULL)
        return RM_FAIL;

    if (array->size + 1 >= array->capacity)
        return RM_FAIL;

    _ensure_cap(array, ( array->size + 1));
    memcpy((array->data)[array->size], value, array->data_size);

    array->size++;

    return RM_SUCCESS;
}

int rm_list_insert(rm_list *array, const size_t index, const void *value)
{
    if (array == NULL)
        return RM_FAIL;

    if (index >= array->capacity)
        return RM_FAIL;

    memcpy((array->data)[index], value, array->data_size);

    return RM_SUCCESS;
}

int rm_list_delete(rm_list *array, const size_t index)
{
    int status;
    int from;
    int to;

    rm_list tmp;

    if (array == NULL)
        return RM_FAIL;

    if (index < 0 || index >= array->capacity)
        return RM_FAIL;

    from = 0;
    to = 0;
    rm_list_init(&tmp, array->data_size);

    while (from <= array->size)
    {
        if (from == index)
        {
            from++;
            continue;
        }

        memcpy(tmp.data[to], array->data[from], array->data_size);

        from++;
        to++;
    }

    array->size--;

    rm_list_copy(array, &tmp);
    rm_list_destroy(&tmp);

    return RM_FAIL;
}

int rm_list_get(rm_list *array, const size_t index, void *value)
{

    if (array == NULL)
        return RM_FAIL;

    if (index < 0 || index >= array->capacity)
        return RM_FAIL;

    memcpy(value, (array->data)[index], array->data_size);

    return RM_SUCCESS;
}

int rm_list_clear(rm_list *array)
{
    int index;

    if (array == NULL)
        return RM_FAIL;

    index = 0;

    while (index < array->size)
        memset((array->data)[index++], 0, array->data_size);

    return RM_SUCCESS;
}

#endif // rm_list
