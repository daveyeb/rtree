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
#include <memory>

// external libs
#include "tinydir.h"

#if (defined _MSC_VER || defined __MINGW32__)
#include <direct.h>
#include <io.h>
#include <fcntl.h>
#define cwd _getcwd
#define stat _stat
#else
#include <unistd.h>
#define cwd getcwd
#endif

inline int iseq(std::string x, std::string y)
{
    return x.compare(y) == 0;
}

// Modified isalnum
inline int isalnum_mod(int x)
{
    return isalnum(x) || x == 95 || x == 36;
}

// Modified iscntrl
inline int iscntrl_mod(int x){
    return iscntrl(x) || (x <= 31) || (x == 127);
}

inline int issdb(int x)
{
    return (x == 34 || x == 39 || x == 96);
}

inline std::string lower(std::string x)
{
    std::string r = x;
    std::transform(r.begin(), r.end(), r.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    return r;
}

inline int strcon(std::string x, std::string y)
{
    return std::string(x).find(std::string(y)) != std::string::npos;
}

template <typename T>
inline int find(T v, std::string x)
{
    return std::find(v.begin(), v.end(), x) != v.end();
}

inline std::string rt_cwd()
{
    char dir[FILENAME_MAX];
    cwd(dir, FILENAME_MAX);
    return std::string(dir);
}

inline std::pair<std::string, size_t> xPattern(std::string path, std::string pattern)
{

    size_t findex, lfound = 0, count = 0; // first index, last found and count

    while ((findex = path.find(pattern, lfound)) != std::string::npos)
    {
        lfound = findex + 1;
        count++;
    }

    return {path.substr(lfound, path.length()), count};
}

inline std::string resolve(std::string parent, std::string dep)
{
    size_t i = 0, foundIndex, upArrCnt;

    std::pair<std::string, size_t> baseCnt = xPattern(dep, "../");
    std::string baseName = std::get<0>(baseCnt);
    upArrCnt = std::get<1>(baseCnt);

    while (i <= upArrCnt)
    {
        foundIndex = parent.find_last_of("/");

        if (foundIndex != std::string::npos)
            parent = parent.substr(0, foundIndex);

        i++;
    }

    // TODO : concate extensions to find in all files if path had no ext

    return (parent + baseName.substr(1));

} // resolve paths

#endif