#include <fcntl.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    int fd = open("tmp.txt", O_CREAT | O_WRONLY);
    if (fd < 0)
        errExit("Open failed");

    int flags = fcntl(fd, F_GETFL);
    if (flags < 0)
        errExit("F_GETFL failed");
    int accessMode = flags & O_ACCMODE;
    switch (accessMode)
    {
    case O_RDONLY:
        printf("Opened in read-only mode\n");
        break;
    case O_WRONLY:
        printf("Opened in write-only mode\n");
        break;
    case O_RDWR:
        printf("Opened in read-write mode\n");
        break;
    default:
        errExit("Unknown accessMode %#X\n", accessMode);
    }

    if (flags & O_APPEND)
        errExit("Opend with append mode\n");
    else
        printf("Opend without append mode\n");
    flags |= O_APPEND;
    if (fcntl(fd, F_SETFL, flags) < 0)
        errExit("F_SETFL failed");
    flags = fcntl(fd, F_GETFL);
    if (flags < 0)
        errExit("F_GETFL failed");
    if (flags & O_APPEND)
        printf("Append flag is now set.\n");
    else
        errExit("Append flag set failed!");

    close(fd);
    return 0;
}
