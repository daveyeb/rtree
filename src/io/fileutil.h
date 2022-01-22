#ifndef __RT__FILE__H__
#define __RT__FILE__H__

#include "common.h"
#include "syntax/syn_analysis.h"

#include "languages/JavaScript.h"

namespace RTree
{

    struct rtFile
    {
        std::string name;
        std::string ext;
        std::string chunk;

        bool operator<(const rtFile &ob) const
        {
            return name.compare(ob.name) < 0;
        }
    };

    class FileUtil
    {
    private:
        std::vector<rtFile> _files;
        std::vector<std::string> _exts;

    public:
        FileUtil();
        virtual ~FileUtil();

        void readCWD(const std::string dir = rt_cwd());
        std::string chunks(char * path);
        std::vector<rtFile> files() const {
            return _files;
        };

        std::shared_ptr<SynAnalysis> synAnalysis(std::string ext)
        {
            std::shared_ptr<SynAnalysis> ptr = nullptr;
            if (iseq(ext, "js") || iseq(ext, "ts"))
                ptr = std::shared_ptr<RTJavaScript>( new RTJavaScript );

            return ptr;
        }
    };

}

#endif
