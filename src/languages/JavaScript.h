#ifndef __RT__JAVASCRIPT__H__
#define __RT__JAVASCRIPT__H__

#include "common.h"

class Parser; 

class JavaScript
{
public:
    static void parse(Parser *const p, std::set<std::string> &mods);
};


#endif