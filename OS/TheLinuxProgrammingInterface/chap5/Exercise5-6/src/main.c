#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
        usageErr("program <file>");

    const char *const file = argv[1];
    int fd1 = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd1 < 0)
        errExit("Failed to open %s", file);
    int fd2 = dup(fd1);
    if (fd2 < 2)
        errExit("Failed to dup.");
    int fd3 = open(file, O_RDWR);
    if (fd3 < 0)
        errExit("Failed to open %s again.", file);
    write(fd1, "Hello,", 6);
    write(fd2, "world", 6);
    lseek(fd2, 0, SEEK_SET);
    write(fd1, "HELLO,", 6);
    write(fd3, "Gidday", 6);

    close(fd3);
    close(fd2);
    close(fd1);

    return 0;
}
