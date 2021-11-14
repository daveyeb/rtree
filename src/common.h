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

int iseq(std::string x, std::string y)
{
    return x.compare(y) == 0;
}

// Modified isalnum
int isalnum_mod(int x)
{
    return isalnum(x) || x == 95 || x == 36;
}

int issdb(int x)
{
    return (x == 34 || x == 39 || x == 96);
}

std::string lower(std::string x)
{
    std::string r = x;
    std::transform(r.begin(), r.end(), r.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    return r;
}

int contains(std::string x, std::string y)
{
    return std::string(x).find(std::string(y)) != std::string::npos;
}

int find(std::string v, std::string x)
{
    return std::find(v.begin(), v.end(), x) != v.end();
}

// typedef void (*lang)(Parser *p, std::set<std::string> &deps);

#endif