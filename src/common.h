#ifndef __RT__COMMON__H__
#define __RT__COMMON__H__

#include <string>
#include <vector>
#include <set>
#include <cctype>
#include <algorithm>

#define IS_EQ(x, y) \
    (std::string(x).compare(std::string(y)) == 0)

#define IS_ALNUM(x) \
    (isalnum(x) || x == 95 || x == 36)

#define TO_LOWER(x) (         \
    {                         \
        for (auto &ch : x)    \
            ch = tolower(ch); \
        x;                    \
    })

#define IS_CTRL(x) \
    ((x <= 31) || (x == 127))

#define IS_SDB(x) \
    (x == 34 || x == 39 || x == 96)

// #define 

#endif