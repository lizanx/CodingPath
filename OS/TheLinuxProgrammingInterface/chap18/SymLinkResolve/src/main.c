#define _DEFAULT_SOURCE
#include <limits.h>
#include <sys/stat.h>
#include "tlpi_hdr.h"

/*
touch a
ln -s a b
./build/program b
*/

int main(int argc, char *argv[])
{
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s <file path>\n", argv[0]);

    const char *filepath = argv[1];
    struct stat st;
    if (lstat(filepath, &st))
        errExit("lstat");
    if (!S_ISLNK(st.st_mode))
        fatal("%s isn't a symbolic link.", filepath);

    char buf[PATH_MAX];
    ssize_t cnt = readlink(filepath, buf, sizeof(buf) - 1);
    if (cnt < 0)
        errExit("readlink");
    buf[cnt] = '\0';
    printf("readlink: %s --> %s\n", filepath, buf);

    if (!realpath(filepath, buf))
        errExit("relapath");
    printf("relapath: %s --> %s\n", filepath, buf);

    return 0;
}
