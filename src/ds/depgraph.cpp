#include "depgraph.h"

namespace RTToken
{
    DepGraph::DepGraph(size_t size)
    {
        l.resize(size);
        _files = size;
        _dependants = 0;
    }

    DepGraph::~DepGraph()
    {
        l.clear();
    }

    void DepGraph::addDep(std::string parent, std::set<std::string> deps)
    {
        _dependants += deps.size();

        for (auto &dep : deps)
        {
            l[parent].push_back(dep);
        }
    }

    void DepGraph::print() const
    {
        std::vector<std::string> innerPointers = {"├───", "│   "};
        std::vector<std::string> outerPointers = {"└───", "    "};
        std::set<std::string>::iterator sIt;
        std::vector<std::string> pointers[2];
        std::string baseName;


    }

    void DepGraph::summary() const {
        
    }

}