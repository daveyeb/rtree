#ifndef RM_STRING
#define RM_STRING


#include <ctype.h>
#include "rm_types.h"

#define issdq(c) \
    (c == 34 || c == 39 || c == 96)

#define isalnd(c) \
    (isalnum(c) || c == 95 || c == 36)

#define isscont(a, b) \
    (rm_str(a).find(rm_str(b)) != rm_str::npos)

#define isseq(a, b) \
    (rm_str(a).compare(rm_str(b)) == 0)

#define rm_strcat(a, b) \
    (rm_str(a) + rm_str(b))

#define rm_tolower(a)         \
    int i = 0;                \
    while (i < a.length())    \
    {                         \
        a[i] = tolower(a[i]); \
        i++;                  \
    }

#endif // !RM_STRING