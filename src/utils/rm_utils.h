#ifndef RM_UTILS
#define RM_UTILS


// supported file extensions
#define EXT    \
    {".rb",    \
     ".java",  \
     ".Swift", \
     ".js"};

// definitions
#define rm_func static inline

// utility functions

#define rm_fforeach(x)       \
    {                        \
        int i = 0;           \
        while (i < x.size()) \
        {

#define rm_fforend() \
    i++;             \
    }                \
    }

#endif // !RM_UTILS