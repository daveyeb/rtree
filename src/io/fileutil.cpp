#include "fileutil.h"

namespace RTree
{

    FileUtil::FileUtil()
    {
        _exts.push_back(".js");
        _exts.push_back(".ts");
    }

    FileUtil::~FileUtil()
    {
        _files.clear();
    }

    void FileUtil::readCWD(const std::string dir)
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

            rtFile some = {tf.path, tf.extension, chunks(tf.path)};
            _files.push_back(some);

            tinydir_next(&td);
        }
        tinydir_close(&td);
    }

    std::string FileUtil::chunks(char *path)
    {
        char ch;
        std::string buffer;
        FILE *fptr = nullptr;

        fptr = fopen(path, "r");

        if (fptr == nullptr)
            return "";

        while (1)
        {
            ch = fgetc(fptr);

            if (feof(fptr))
                break;

            buffer += ch;
        }

        fclose(fptr);
        fptr = nullptr;

        return buffer;
    }

}
