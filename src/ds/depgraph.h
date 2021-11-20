#ifndef __RT__DEPGRAPH__H__
#define __RT__DEPGRAPH__H__

#include "common.h"

namespace RTToken
{

    class DepGraph
    {
    private:
        std::vector<std::vector<std::string>> l;
        size_t _files;
        size_t _dependants; 

    public:
        DepGraph(size_t size);
        virtual ~DepGraph();

        void print() const;
        void summary() const;
        void addDep(std::string parent, std::set<std::string> deps);
    };

}

#endif