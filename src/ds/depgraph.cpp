#include "depgraph.h"

namespace RTree
{
    DepGraph::DepGraph(size_t size)
    {
        _files = size;
        _dependants = 0;
        _filesPrinted = 0;
        _isFull = false;
    }

    DepGraph::~DepGraph()
    {
        l.clear();
    }

    void DepGraph::setFull()
    {
        _isFull = true;
    }

    void DepGraph::setDeps()
    {
        _isDeps = true;
    }

    void DepGraph::addDep(std::string parent, std::set<std::string> deps)
    {
        _dependants += deps.size();

        for (auto &dep : deps)
        {
            l[parent].push_back(dep);
        }

        if(_isDeps && deps.empty()) return;

        _print(parent, deps);
    }

    void DepGraph::_print(std::string parent, std::set<std::string> deps)
    {
        std::vector<std::string> innerPointers = {"├───", "│   "};
        std::vector<std::string> outerPointers = {"└───", "    "};
        std::vector<std::string> pointers[2];

        std::set<std::string>::iterator it;

        size_t size = l.size();

        std::string baseName = xPattern(parent, "/").first;
        pointers[0] = _filesPrinted == _files - 1 ? outerPointers : innerPointers;
        _filesPrinted++;
        // printing source file name

#if (defined _MSC_VER || defined __MINGW32__)
        _setmode(_fileno(stdout), _O_WTEXT);
        std::cout << pointers[0][0];
        _setmode(_fileno(stdout), _O_TEXT);
#else
        std::cout << pointers[0][0] << " " << baseName << std::endl;
#endif

        // printing deps

        for (it = deps.begin(); it != deps.end(); ++it)
        {
            pointers[1] = it == --(deps.end()) ? outerPointers : innerPointers;

#if (defined _MSC_VER || defined __MINGW32__)
            _setmode(_fileno(stdout), _O_WTEXT);
            std::cout << pointers[0][1] << pointers[1][0];
            _setmode(_fileno(stdout), _O_TEXT);
#else
            std::cout << pointers[0][1]  << " " << pointers[1][0] ;
#endif

            if (_isFull)
            {
                if (strcon(*it, "./"))
                    std::cout << " " << resolve(parent, *it) << "\n";
                else
                    std::cout << " " << *it << std::endl;
            }
            else
            {
                std::cout << " " << *it << std::endl;
            }
        }
    }

    void DepGraph::summary() const
    {

        std::cout << "\n"
                  << _dependants << " dependants, " << _files << " files" << std::endl;
    }

}