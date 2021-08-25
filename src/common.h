#ifndef __RT__COMMON__H__
#define __RT__COMMON__H__

#include <string>
#include <vector>
#include <set>
#include <map>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <utility>
#include <assert.h>
#include <typeinfo>
#include <typeindex>
#include <fstream>

#if (defined _MSC_VER || defined __MINGW32__)
#include <direct.h>
#include <io.h>
#include <fcntl.h>
#define CURRENT_PATH _getcwd
#define STAT _stat
#else
#include <unistd.h>
#define CURRENT_PATH getcwd
#define STAT stat
#endif

class Parser;

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

#define STR_CON(x, y) \
    (std::string(x).find(std::string(y)) != std::string::npos)

#define FIND(v, x) \
    (std::find(v.begin(), v.end(), x) != v.end())

typedef void (*lang)(Parser *p, std::set<std::string> &deps);

#endif