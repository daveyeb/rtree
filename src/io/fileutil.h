#ifndef __RT__FILE__H__
#define __RT__FILE__H__

#include "common.h"
#include "syntax/syn_analysis.h"

namespace RTToken
{

    struct rtFile
    {
        std::string name;
        std::string content;
    };

    class FileUtil
    {
    private:
        std::vector<tinydir_file> _files;
        std::vector<std::string> _exts;

        std::map<rtFile, std::unique_ptr<SynAnalysis>> _chunks;

        std::unique_ptr<SynAnalysis> _langType(std::string ext)
        {

            if (iseq(ext, "js") || iseq(ext, "ts"))
                return std::unique_ptr<RTJavaScript>();
        }

    public:
        FileUtil();
        virtual ~FileUtil();

        void readCWD(const std::string dir = rt_cwd());
        std::map<rtFile, std::unique_ptr<SynAnalysis>> &chunks(); // chunks w syntax to analyze w
    };

}

#endif