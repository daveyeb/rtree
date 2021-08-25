#ifndef __RT__FILE__H__
#define __RT__FILE__H__

#include "common.h"


class FileService
{
private:
    static const std::vector<std::string> extensions;

public:
    static void readDir(const std::string dir, std::map<std::string, lang> &readFiles);
    static std::string readFile(const std::string file);
    static std::string resolvePath(std::string parent, std::string path);
    static std::pair<std::string, size_t> removePattern(std::string path, std::string pattern);
    static std::string currentDir();
    static lang getLangType(std::string ext);
};

#endif