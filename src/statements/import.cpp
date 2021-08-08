#include "import.h"

Import::Import(size_t l, std::string n, std::string d)
{
    level = l;
    name = n;
    dependant = d;
}

Import::~Import()
{
}