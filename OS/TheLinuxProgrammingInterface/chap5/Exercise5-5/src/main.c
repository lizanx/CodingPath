#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
        usageErr("program <file>");

    const char *file = argv[1];
    int fd = open(file, O_CREAT | O_RDWR);
    if (fd < 0)
        errExit("Failed to open %s", file);
    int flags = fcntl(fd, F_GETFL);
    if (flags < 0)
        errExit("Failed to get flags.");
    off_t pos = lseek(fd, 0, SEEK_CUR);
    if (pos < 0)
        errExit("Failed to lseek.");

    int dupfd = dup(fd);
    if (dupfd < 0)
        errExit("Failed to dup.");
    int dupflags = fcntl(dupfd, F_GETFL);
    if (dupflags < 0)
        errExit("Failed to get dup flags.");
    if (dupflags != flags)
        errExit("Flags of duped fd differ from original one!");
    off_t duppos = lseek(dupfd, 0, SEEK_CUR);
    if (duppos < 0)
        errExit("Failed to lseek.");
    if (duppos != pos)
        errExit("Offset of duped fd differ from original one!");

    pos = lseek(fd, 0, SEEK_END);
    if (pos < 0)
        errExit("Failed to lseek.");
    duppos = lseek(dupfd, 0, SEEK_CUR);
    if (duppos < 0)
        errExit("Failed to lseek.");
    if (duppos != pos)
        errExit("Offset of duped fd differ from original one!");

    if (close(fd) < 0)
        errExit("Failed to close.");
    if (close(dupfd) < 0)
        errExit("Failed to close.");
    printf("All checks pass!");
    return 0;
}
