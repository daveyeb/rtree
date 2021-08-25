#include "file.h"
#include "tinydir.h"

#include "languages/JavaScript.h"


const std::vector<std::string> FileService::extensions =
    {
        //{Java/Type}Script
        ".js",
        ".ts"};

lang FileService::getLangType(std::string ext)
{
    lang res;

    if (IS_EQ(ext, "js") || IS_EQ(ext, "ts"))
        res = JavaScript::parse;

    return res;
}

void FileService::readDir(const std::string dir, std::map<std::string, lang> &readFiles)
{
    tinydir_dir t_dir;
    tinydir_file t_file;
    std::string extension;

    tinydir_open(&t_dir, dir.c_str());

    while (t_dir.has_next)
    {

        tinydir_readfile(&t_dir, &t_file);
        extension = t_file.extension;

        if (t_file.is_dir)
        {
            if (!STR_CON("..", t_file.name))
                readDir(std::string(t_file.path), readFiles);

            tinydir_next(&t_dir);
            continue;
        }

        if (std::string(extension).empty())
        {
            tinydir_next(&t_dir);
            continue;
        }

        if (!FIND(extensions, std::string("." + extension)))
        {
            tinydir_next(&t_dir);
            continue;
        }

        readFiles.insert(std::make_pair(t_file.path, getLangType(extension)));
        tinydir_next(&t_dir);
    }
    tinydir_close(&t_dir);
}

std::string FileService::readFile(const std::string file)
{
    std::string buffer;
    char ch;

    FILE *fptr = fopen(file.c_str(), "r");

    if (fptr == NULL)
        return buffer;

    while (1)
    {
        ch = fgetc(fptr);

        if (feof(fptr))
            break;

        buffer += ch;
    }

    fclose(fptr);
    return buffer;
}

std::pair<std::string, size_t> FileService::removePattern(std::string path, std::string pattern)
{
    size_t foundIndex, last = 0, count = 0;

    while ((foundIndex = path.find(pattern, last)) != std::string::npos)
    {
        last = foundIndex + 1;
        count++;
    }

    return std::make_pair(path.substr(last, path.length()), count);
}

std::string FileService::resolvePath(std::string parent, std::string path)
{
    size_t index = 0, foundIndex, upCount;

    std::pair<std::string, size_t> baseNCnt = removePattern(path, "../");

    std::string baseName = std::get<0>(baseNCnt);
    upCount = std::get<1>(baseNCnt);

    while (index <= upCount)
    {
        foundIndex = parent.find_last_of("/");

        if (foundIndex != std::string::npos)
            parent = parent.substr(0, foundIndex);

        index++;
    }

    //TODO : concate extensions to find in all files if path had no ext

    return (parent + baseName.substr(1));
}

std::string FileService::currentDir()
{
    char fileName[FILENAME_MAX];

    CURRENT_PATH(fileName, FILENAME_MAX);

    return std::string(fileName);
}
