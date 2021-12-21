#ifndef __RT__EXEC__H__
#define __RT__EXEC__H__

#include "common.h"

namespace RTree
{

    typedef void (*option)(void);

    class Exec
    {
    public:
        static int run(int argc, char *argv[]);

        Exec() {}
        ~Exec() {}

    private:
        static std::string _option(std::string op);
    };
}

#endif