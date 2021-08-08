#ifndef __RT__IMPORT_H__
#define __RT__IMPORT_H__

#include "common.h"

class Import
{
private:
    size_t level; 
    std::string basename;
    std::string name;
    std::string dependant;
    
public:
    Import(size_t l, std::string n, std::string d);
    ~Import();
};

#endif