#ifndef RM_FILE_SVC
#define RM_FILE_SVC

// dependacies
#include "tinydir.h"
#include "rm_types.h"
#include "rm_string.h"
#include "rm_utils.h"

/*
    file services
        1. rm_open_dir
        2. rm_read_file
*/

rm_func 
int rm_open_dir(const rm_str dir, rm_sfs &files)
{
    int index;
    int found;
    int size;

    const char *ext[] = EXT;
    rm_map known_ext;

    char *text; // tiny_dir file extension
    tinydir_dir tdir;
    tinydir_file tfile;
    rm_sf cfile;

    if (dir.length() == 0)
        return 1;

    tinydir_open(&tdir, dir.c_str());

    while (tdir.has_next)
    {
        // start blank slate
        cfile.ext.clear();
        cfile.name.clear();
        cfile.path.clear();

        // read file
        tinydir_readfile(&tdir, &tfile);
        text = tfile.extension;

        if (tfile.is_dir)
        {
            if (!isscont("..", tfile.name))
                rm_open_dir(rm_str(tfile.path), files);

            tinydir_next(&tdir);
            continue;
        }

        if (rm_str(text) == "")
        {
            tinydir_next(&tdir);
            continue;
        }

        if (known_ext.find(rm_strcat(".", text)) == known_ext.end())
        {

            index = 0;
            size = sizeof(ext) / sizeof(char *);

            while (index < size)
            {
                found = 0;

                if (rm_strcat(".", text) != ext[index])
                {
                    index++;
                    continue;
                }

                found = 1;
                known_ext.insert(rm_pair(rm_strcat(".", text), found));

                cfile.ext = tfile.extension;
                cfile.name = tfile.name;
                cfile.path = tfile.path;

                files.push_back(cfile);

                if (found)
                    break;

                index++;
            }
        }
        else
        {
            if (!known_ext.find(rm_strcat(".", text))->second)
            {
                tinydir_next(&tdir);
                continue;
            }

            cfile.ext = tfile.extension;
            cfile.name = tfile.name;
            cfile.path = tfile.path;

            files.push_back(cfile);
        }

        tinydir_next(&tdir);
    }

    tinydir_close(&tdir);

    // TODO: test read files on permission restrictions

    return 0;
}

rm_func 
int rm_read_file(rm_sf file, rm_str &buffer)
{
    int ch;
    FILE *fptr;

    fptr = fopen(file.path.c_str(), "r");

    if (fptr == NULL)
        return 1;

    buffer.clear();

    while (1)
    {
        ch = fgetc(fptr);

        if (feof(fptr))
            break;

        buffer += ch;
    }

    fclose(fptr);

    return 0;
}

#endif // !RM_FILE_SVC