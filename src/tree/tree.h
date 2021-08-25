#ifndef __RT__TREE_H__
#define __RT__TREE_H__

#include "common.h"

class Tree
{
private:
    static int files; 
    static int dependants;

    static bool isOnlyDepedants;
    static bool isFull;
    static bool isBase;
    static bool isOutput;

    static std::string filename;
    
public:
    static void print(std::string file, std::set<std::string> dset, bool isEnd);
    static void summary();
    static void toggleBase() { isBase = !isBase; }
    static void toggleFull() { isFull = !isFull; }
    static void toggleDependants() { isOnlyDepedants = !isOnlyDepedants; }
    static void toggleOutput(std::string fname){
        isOutput = !isOutput;
        filename = fname;
    }

};

#endif