#include "exec/exec.h"
#include "docopt.h"
#include "termcolor.hpp"
#include "usage.h"
#include "version.h"

using namespace RTree;

int main(int argc, char **argv)
{

    std::string version = (std::string("\n rTree version: ") + VERSION +
                           std::string("\nH4CkClimate LLC https:://hackclimate.io"));

    docopt::docopt(USAGE,
                   {argv + 1, argv + argc},
                   true,
                   version.c_str());

    return Exec::run(argc, argv);
}