#include "exec.h"
#include "file/file.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "tree/tree.h"
#include "token/token.h"

// TODO : log all return if statements

int Exec::execute(char *argv[])
{
    std::set<std::string> files;
    
    FileService::readDir(FileService::currentDir(), files);

    if (files.empty())
        return 0;

    for (std::string file : files)
    {
        Lexer lexer(FileService::readFile(file));
        Parser parser(lexer.scanTokens());
        Tree::print(file,parser.scanDependencies());
    }

    Tree::summary();

    std::cout << "Done" << "\n";

    return 1;
}