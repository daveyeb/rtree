#include "tree.h"
#include "file/file.h"
#include "common.h"

int Tree::files = 0;
int Tree::dependants = 0;

bool Tree::isBase = false;
bool Tree::isOnlyDepedants = false;
bool Tree::isFull = false;
bool Tree::isOutput = false;

std::string Tree::filename = "";

void Tree::print(std::string file, std::set<std::string> dset, bool isEnd)
{
    std::vector<std::string> innerPointers = {"├───", "│   "};
    std::vector<std::string> outerPointers = {"└───", "    "};
    std::set<std::string>::iterator sIt;
    std::vector<std::string> pointers[2];
    std::string baseName;


// TODO "Implement output feature someday :)"
//     if (isOutput)
//     {
//         std::wofstream output(filename);

//         // assert((output.rdstate() & std::ofstream::goodbit != 0));
// #if (defined _MSC_VER || defined __MINGW32__)
//         std::wcout.rdbuf(output.rdbuf());
//         // std::wcout.rdbuf(output.rdbuf());
//         std::cout.rdbuf(output.rdbuf());
// #else
//     std::cout.rdbuf(output.rdbuf());
// #endif
//     }

    files++;
    if (dset.size())
        dependants++;

    if (isOnlyDepedants)
        if (!dset.size())
            return;

    pointers[0] = isEnd ? outerPointers : innerPointers;
    baseName = FileService::removePattern(file, "/").first;

#if (defined _MSC_VER || defined __MINGW32__)
    _setmode(_fileno(stdout), _O_WTEXT);
    std::cout << pointers[0][0];
    _setmode(_fileno(stdout), _O_TEXT);

    std::cout << baseName << std::endl;
#else

    std::cout << pointers[0][0] << baseName << std::endl;
#endif

    for (sIt = dset.begin(); sIt != dset.end(); ++sIt)
    {
        pointers[1] = (sIt == --(dset.end())) ? outerPointers : innerPointers;

#if (defined _MSC_VER || defined __MINGW32__)
        _setmode(_fileno(stdout), _O_WTEXT);
        std::cout << pointers[0][1] << pointers[1][0];
        _setmode(_fileno(stdout), _O_TEXT);

        if (isFull)
        {
            if (STR_CON(*sIt, "./"))
                std::cout << FileService::resolvePath(file, *sIt) << std::endl;
            else
                std::cout << *sIt << std::endl;

            continue;
        }

        if (isBase)
        {
            std::cout << FileService::removePattern(*sIt, "/").first << std::endl;

            continue;
        }
        std::cout << *sIt << std::endl;

#else
        std::cout << pointers[0];

        if (isFull)
        {
            if (STR_CON(*sIt, "./"))
                std::cout << FileService::resolvePath(file, *sIt) << std::endl;
            else
                std::cout << *sIt << std::endl;

            continue;
        }

        if (isBase)
        {
            std::cout << FileService::removePattern(*sIt, "/").first << std::endl;

            continue;
        }

        std::cout << *sIt << std::endl;
#endif
    }
}

void Tree::summary()
{
    std::cout << "\n"
              << dependants << " dependants, " << files << " files" << std::endl;
}