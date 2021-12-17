#include "common.h"
#include "exec/exec.h"
#include "docopt.h"
#include "termcolor.hpp"
#include "usage.h"
#include "version.h"

using namespace RTToken;

int main(int argc, char **argv)
{

    std::string version = (std::string("\n rTree version: ") + VERSION +
                           std::string("\nHackClimate LLC https:://hackclimate.io"));

    docopt::docopt(USAGE,
                   {argv + 1, argv + argc},
                   true,
                   version.c_str());

    return Exec::run(argc, argv);
}