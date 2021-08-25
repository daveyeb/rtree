#include "exec.h"
#include "file/file.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "tree/tree.h"
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

void full()
{
    Tree::toggleFull();
}

void base()
{
    Tree::toggleBase();
}

void dependants()
{
    Tree::toggleDependants();
}

// void output(int argc, char **argv)
// {
//     std::cout << argv[2] << "\n";

//     std::string fn(argv[2]);

//     Tree::toggleOutput(fn);
// }

std::string getCmdType(std::string cmd)
{
    std::string res;

    if (IS_EQ(cmd, "-d"))
        res = "dependants";
    else if (IS_EQ(cmd, "-f"))
        res = "full";
    else if (IS_EQ(cmd, "-b"))
        res = "base";
    // else if (IS_EQ(cmd, "-o"))
    //     res = "output";

    if (res.empty())
        res = cmd.substr(2);

    return res;
}

int Exec::execute(int argc, char *argv[])
{

    FunctionCaller fc;

    std::map<std::string, lang> files;
    std::map<std::string, lang>::iterator fIt;

    fc.insert("full", full);
    fc.insert("base", base);
    fc.insert("dependants", dependants);
    // fc.insert("output", output);

    if (argc >= 2)
    {
        std::string cmd(argv[1]);
        cmd = getCmdType(cmd);
        fc.callFunction<void>(cmd, argc, argv);
    }

    FileService::readDir(FileService::currentDir(), files);

    if (files.empty())
        return 0;

    fIt = files.begin();

    std::cout << "./" << std::endl;

    for (const auto &fpair : files)
    {
        Lexer lexer(FileService::readFile(fpair.first));
        Parser parser(lexer.scanTokens());
        Tree::print(fpair.first, parser.scanDependencies(fpair.second), ++fIt == files.end());
    }

    Tree::summary();

    return 1;
}