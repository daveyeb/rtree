#ifndef __RT__DEPGRAPH__H__
#define __RT__DEPGRAPH__H__

#include "common.h"

namespace RTree
{

    class DepGraph
    {
    private:
        std::map<std::string, std::vector<std::string> > l;
        size_t _files;
        size_t _dependants;
        size_t _filesPrinted;
        bool _isFull;
        bool _isDeps;

        void _print(std::string parent, std::set<std::string> deps);

    public:
        DepGraph(size_t size);
        virtual ~DepGraph();

        void summary() const;
        void addDep(std::string parent, std::set<std::string> deps);

        void setFull();
        void setDeps();
    };

}

#endif