#ifndef __RT__JAVASCRIPT__H__
#define __RT__JAVASCRIPT__H__

#include "common.h"
#include "syntax/syn_analysis.h"

namespace RTToken
{
    class Parser;

    class RTJavaScript : SynAnalysis
    {
    public:
        RTJavaScript();
        virtual ~RTJavaScript();

        void parse(Parser *const p);
        const std::set<std::string>& deps() const;
        
    };
}

#endif