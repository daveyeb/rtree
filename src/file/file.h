#ifndef __RT__FILE__H__
#define __RT__FILE__H__

#include "common.h"

class FileService
{
private:
    static const std::vector<std::string> extensions;

public:
    static void readDir(const std::string dir, std::set<std::string> &readFiles);
    static std::string readFile(const std::string file);
    static std::string resolvePath(std::string parent, std::string path);
    static std::pair<std::string, size_t> baseName(std::string path);
    static std::string currentDir();
};

#endif