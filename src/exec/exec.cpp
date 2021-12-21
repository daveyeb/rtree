#include "exec/exec.h"
#include "io/fileutil.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "ds/depgraph.h"
#include "token/token.h"


namespace RTree
{

    std::string Exec::_option(std::string op)
    {
        if (iseq(op, "-d"))
            return "dependents";
        else if (iseq(op, "-f"))
            return "full";

        return "";
    }

    int Exec::run(int argc, char *argv[])
    {
        std::string cmd;
        std::vector<rtFile> files; // parsable files
        FileUtil fileUtil;

        if (argc >= 2)
        {
            cmd = std::string(argv[1]);
            cmd = Exec::_option(cmd);

            assert(!iseq("", cmd));
        }

        // read current directory for files
        fileUtil.readCWD();
        files = fileUtil.files();

        DepGraph depGraph(fileUtil.files().size());

        if (iseq("full", cmd))
            depGraph.setFull();

        if (iseq("dependents", cmd))
            depGraph.setDeps();

        for (auto &file : files)
        {
            Lexer lexer(file.chunk); // load chunk into lexer
            Parser parser(lexer.scanTokens()); // load tokens into parser
            depGraph.addDep(file.name, parser.scanDependencies(fileUtil.synAnalysis(file.ext))); // insert parsed deps to graph

        }

        depGraph.summary();

        return 1;
    }

}
