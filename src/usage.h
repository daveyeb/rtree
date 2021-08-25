#ifndef __RT__USAGE__
#define __RT__USAGE__

static const char USAGE[] = 
R"(
Usage:
    rtree
    rtree [-f | --full]
    rtree [-b | --base]
    rtree [-d | --dependants]
Commands:
    full        Lists only full pathnames of imported files
    base        Lists only basename of imported files  
    dependants  Lists only dependants 
    level       Lists dependancy tree at a level/depth 
    output      Outputs results to a file 
Options:
    --version   Shows version.


If you need assistance, feel free to contact me:
    https://twitter.com/daveyeb

)";

#endif