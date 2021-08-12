#ifndef __RT__TREE_H__
#define __RT__TREE_H__

#include "common.h"

class Tree
{
private:
    std::map<std::string, std::set<std::string>> t;
    static int files; 
    static int dependants;
    
public:
    void insert(std::string file, std::set<std::string> dset);
    static void print(std::string file, std::set<std::string> dset);
    static void summary();
};

#endif