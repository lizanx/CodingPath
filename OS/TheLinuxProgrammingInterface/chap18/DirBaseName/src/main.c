#define _DEFAULT_SOURCE
#include <libgen.h>
#include <string.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s <path list...>\n", argv[0]);

    for (int i = 1; i < argc; ++i)
    {
        char *path1 = strdup(argv[i]);
        if (!path1)
            errExit("strdup");
        char *path2 = strdup(argv[i]);
        if (!path2)
            errExit("strdup");
        const char *dir = dirname(path1);
        const char *base = basename(path2);
        printf("%s\t\tBase[%s]\tDir[%s]\n", argv[i], base, dir);
        free(path1);
        free(path2);
    }

    return 0;
}
