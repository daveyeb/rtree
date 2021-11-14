#ifndef __RT__SYN_ANALYSIS_H__
#define __RT__SYN_ANALYSIS_H__

#include "common.h"

namespace RTToken
{

    class Parser;

    class SynAnalysis
    {

    public:
        virtual void parse(Parser *const p);
        virtual const std::set<std::string>& deps() const = 0;

    protected:
        std::set<std::string> _deps;
    };

}

#endif