#ifndef __RT__PARSER__H__
#define __RT__PARSER__H__

#include "common.h"
#include "scanner/scanner.h"
#include "syntax/syn_analysis.h"

namespace RTree
{

    class Token;

    class Parser : public Scanner<Token>
    {

    public:
        Parser(std::vector<Token> t);
        virtual ~Parser();

        Token current() const;
        Token next();

        std::vector<Token> peek(size_t n) const;
        std::set<std::string> scanDependencies(std::shared_ptr<SynAnalysis> sa);

    private:
        std::vector<Token> _tokens;
        std::set<std::string> _deps;
    };

}

#endif