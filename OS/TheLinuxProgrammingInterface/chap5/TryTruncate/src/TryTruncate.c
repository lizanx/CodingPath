#define _XOPEN_SOURCE 700
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "tlpi_hdr.h"

static void TryTruncate(const char *file)
{
    int fd = open(file, O_RDONLY);
    if (fd < 0)
        errExit("Failed to open %s", file);
    off_t fileSize = lseek(fd, 0, SEEK_END);
    if (fileSize < 0)
        errExit("Failed to lseek.");
    close(fd);
    printf("Original file size: %ld\n", fileSize);

    printf("Truncating %s ..\n", file);
    if (truncate(file, fileSize / 2) < 0)
        errExit("Failed to truncate %s.", file);

    fd = open(file, O_RDONLY);
    if (fd < 0)
        errExit("Failed to open %s", file);
    fileSize = lseek(fd, 0, SEEK_END);
    if (fileSize < 0)
        errExit("Failed to lseek.");
    close(fd);
    printf("Truncated file size: %ld\n", fileSize);
}

static void TryFtruncate(int fd)
{
    off_t fileSize = lseek(fd, 0, SEEK_END);
    if (fileSize < 0)
        errExit("Failed to lseek.");
    printf("Original file size: %ld\n", fileSize);

    printf("Ftruncating..\n");
    if (ftruncate(fd, fileSize / 3) < 0)
        errExit("Failed to ftruncate %d.", fd);

    fileSize = lseek(fd, 0, SEEK_END);
    if (fileSize < 0)
        errExit("Failed to lseek.");
    printf("Ftruncated file size: %ld\n", fileSize);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
        usageErr("TryTruncate [truncate|ftruncate] <file>");

    if (strcmp(argv[1], "truncate") == 0)
    {
        TryTruncate(argv[2]);
    }
    else if (strcmp(argv[1], "ftruncate") == 0)
    {
        int fd = open(argv[2], O_RDWR);
        if (fd < 0)
            errExit("Failed to open %s.", argv[2]);
        TryFtruncate(fd);
        close(fd);
    }
    else
    {
        usageErr("TryTruncate [truncate|ftruncate] <file>");
    }

    return 0;
}
