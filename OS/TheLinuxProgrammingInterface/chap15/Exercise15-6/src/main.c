#include <sys/stat.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
        usageErr("program <file list>\n"
                 "\t(Same as 'chmod a+rX <files..>')");

    struct stat st;
    for (int i = 1; i < argc; ++i)
    {
        if (stat(argv[i], &st))
        {
            errMsg("Failed to stat %s\n", argv[i]);
            continue;
        }

        mode_t mode = st.st_mode;
        mode |= (S_IRUSR | S_IRGRP | S_IROTH);
        if (S_ISDIR(st.st_mode) || (st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
            mode |= (S_IXUSR | S_IXGRP | S_IXOTH);

        if (chmod(argv[i], mode))
        {
            errMsg("Failed to change mode to %#o for %s\n", mode, argv[i]);
            continue;
        }
    }

    return 0;
}
