#ifndef __RT__JAVASCRIPT__H__
#define __RT__JAVASCRIPT__H__

#include "common.h"
#include "syntax/syn_analysis.h"

namespace RTree
{
    class Parser;

    class RTJavaScript : public SynAnalysis
    {
    public:
        RTJavaScript();
        virtual ~RTJavaScript();

        void parse(Parser *const p, std::set<std::string> &str);
        std::set<std::string> deps() const;
        
    };
}

#endif