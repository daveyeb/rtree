#include "exec.h"
#include "io/fileutil.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "ds/depgraph.h"
#include "token/token.h"

// TODO : log all return if statements

typedef void (*cmds)(void);

struct FunctionCaller
{
    std::map<std::string, cmds> c;

    template <typename T>
    void insert(std::string name, T func)
    {
        auto tt = std::type_index(typeid(func));

        c.insert(std::make_pair(name, (cmds)func));
    }

    template <typename T, typename... Args>
    T callFunction(std::string string_name, Args... args)
    {
        auto iter = c.find(string_name);
        auto mapVal = iter->second;
        auto typeCasted = (T(*)(Args...))(mapVal);

        assert(iter != c.end());

        return typeCasted(std::forward<Args>(args)...);
    }
};

// void full()
// {
//     Tree::toggleFull();
// }

// void base()
// {
//     Tree::toggleBase();
// }

// void dependants()
// {
//     Tree::toggleDependants();
// }

// void output(int argc, char **argv)
// {
//     std::cout << argv[2] << "\n";

//     std::string fn(argv[2]);

//     Tree::toggleOutput(fn);
// }

// std::string getCmdType(std::string cmd)
// {
//     std::string res;

//     if (IS_EQ(cmd, "-d"))
//         res = "dependants";
//     else if (IS_EQ(cmd, "-f"))
//         res = "full";
//     else if (IS_EQ(cmd, "-b"))
//         res = "base";
//     // else if (IS_EQ(cmd, "-o"))
//     //     res = "output";

//     if (res.empty())
//         res = cmd.substr(2);

//     return res;
// }

namespace RTToken
{

    int Exec::run(int argc, char *argv[])
    {

        std::map<rtFile, std::unique_ptr<SynAnalysis>> csas; // chunks w syn analysis
        FileUtil fu;
        DepGraph dg(csas.size());

        // read current directory for files
        fu.readCWD();
        // get chunks
        csas = fu.chunks();

        for (auto &csa: csas)
        {
            rtFile file = csa.first;
            
            Lexer l(file.content); // load chunk into lexer 
            Parser p(l.scanTokens()); // load tokens into parser
            dg.addDep(file.name, p.scanDependencies(csa.second)); // insert parsed deps to graph

        }

        return 1;
    }

}
