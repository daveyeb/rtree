#include "tree.h"

int Tree::dependants = 0;
int Tree::files = 0;

void Tree::insert(std::string file, std::set<std::string> dset)
{
    if (file.empty())
        return;

    t.insert(std::pair<std::string, std::set<std::string>>(file, dset));
}

void Tree::print(std::string file, std::set<std::string> dset)
{
    std::vector<std::wstring> innerPointers = {L"├─── ", L"│   "};
    std::vector<std::wstring> outerPointers = {L"└─── ", L"    "};
    std::set<std::string>::iterator sIt;
    std::vector<std::wstring> pointers;

    std::cout << file << std::endl;
    dependants++;

    for (sIt = dset.begin(); sIt != dset.end(); ++sIt)
    {
        pointers = (sIt == --(dset.end())) ? outerPointers : innerPointers;
        files++;

#ifndef WINDOWS
        _setmode(_fileno(stdout), _O_WTEXT);
        std::wcout << pointers[0];
        _setmode(_fileno(stdout), _O_TEXT);

        std::cout << *sIt << std::endl;
#else
        std::cout << pointers[0] << *sIt << std::endl;
#endif
    }
}

void Tree::summary()
{
    std::cout << "\n"
              << dependants << " dependants, " << files << " files" << std::endl;
}