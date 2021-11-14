#ifndef __RT__FILE__H__
#define __RT__FILE__H__

#include "common.h"
#include "syntax/syn_analysis.h"


class FileUtil
{
private:
    std::vector<std::string> extensions;
    std::map<std::string, std::unique_ptr<SynAnalysis>> files;

public:
    void readDir(const std::string dir);
    std::string readFile(const std::string file);
    std::string resolvePath(std::string parent, std::string path);
    std::pair<std::string, size_t> removePattern(std::string path, std::string pattern);
    std::string currentDir();
    // lang getLangType(std::string ext);
};

#endif