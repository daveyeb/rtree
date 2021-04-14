#include <stdlib.h>
#include <stdio.h>

#define SUPPORTED_EXT {1, 2};

int main()
{
    int safe[] = SUPPORTED_EXT;
    //   printf(SUPPORTED_EXT);

    for (int a = 0; a < sizeof(safe) / sizeof(int); a++)
    {
        printf("%d ", safe[a]);
    }

    return 0;
}