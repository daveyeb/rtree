#include "file.h"
#include "tinydir.h"

const std::vector<std::string> FileService::extensions =
    {
        //{Java/Type}Script
        ".js",
        ".ts"};

void FileService::readDir(const std::string dir, std::set<std::string> &readFiles)
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

        readFiles.insert(t_file.path);
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

#if FILER
    std::cout << file << std::endl;
#endif

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

std::pair<std::string, size_t> FileService::baseName(std::string path)
{
    size_t foundIndex, last, count = 0;

    while ((foundIndex = path.find("../", last)) != std::string::npos)
    {
        last = foundIndex + 1;
        count++;
    }

    return std::make_pair(path.substr(last + 1, path.length()), count);
}

std::string FileService::resolvePath(std::string parent, std::string path)
{
    size_t index, foundIndex, upCount;

    std::pair<std::string, size_t> baseNCnt = baseName(path);

    std::string bN = std::get<0>(baseNCnt);
    upCount = std::get<1>(baseNCnt);

    while (index <= upCount)
    {
        foundIndex = parent.find_last_of("/");

        if (foundIndex != std::string::npos)
            parent = parent.substr(0, foundIndex);

        index++;
    }

    return (parent + bN);
}

std::string FileService::currentDir()
{
    char fileName[FILENAME_MAX];

    CURRENT_PATH(fileName, FILENAME_MAX);

    return std::string(fileName);
}
