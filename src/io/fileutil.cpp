#include "fileutil.h"

namespace RTToken
{

    FileUtil::FileUtil()
    {
    }

    FileUtil::~FileUtil()
    {
        _files.clear();
        _chunks.clear();
    }

    void FileUtil::readCWD(const std::string dir = rt_cwd())
    {
        tinydir_dir td;
        tinydir_file tf;
        std::string ext;

        tinydir_open(&td, dir.c_str());

        while (td.has_next)
        {
            tinydir_readfile(&td, &tf);
            ext = tf.extension;

            if (tf.is_dir)
            {
                if (!strcon("..", tf.name))
                    readCWD(tf.path);

                tinydir_next(&td);
                continue;
            }

            if (ext.empty())
            {
                tinydir_next(&td);
                continue;
            }

            if (!find(_exts, std::string("." + ext)))
            {
                tinydir_next(&td);
                continue;
            }

            _files.push_back(tf);
            tinydir_next(&td);
        }
        tinydir_close(&td);
    }

    std::map<rtFile, std::unique_ptr<SynAnalysis>> &FileUtil::chunks()
    {
        char ch;
        std::string buffer;
        FILE *fptr = nullptr;

        for (auto &file : _files)
        {
            fptr = fopen(file.path, "r");

            if (fptr == nullptr)
                continue;

            while (1)
            {
                ch = fgetc(fptr);

                if (feof(fptr))
                    break;

                buffer += ch;
            }

            fclose(fptr);
            fptr = nullptr;

            //populating _chunks
            _chunks.insert({{file.path, buffer}, _langType(file.extension)});
        }

        return _chunks;
    }

}