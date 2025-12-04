#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "tlpi_hdr.h"

static int dupImpl(int fd)
{
    int newFd = fcntl(fd, F_DUPFD);
    if (newFd < 0)
    {
        fprintf(stderr, "Failed to dup %d\n", fd);
        return -1;
    }
    return newFd;
}

static int dup2Impl(int oldfd, int newfd)
{
    if (oldfd == newfd)
    {
        if (fcntl(oldfd, F_GETFL) < 0)
        {
            fprintf(stderr, "Invalid file descriptor %d\n", oldfd);
            errno = EBADF;
            return -1;
        }
    }
    if (close(newfd) < 0)
    {
        fprintf(stderr, "Failed to close %d\n", newfd);
        return -1;
    }
    int fd = fcntl(oldfd, F_DUPFD);
    if (fd < 0)
    {
        fprintf(stderr, "Failed to fcntl dup %d\n", oldfd);
        return -1;
    }
    return fd;
}

int main(int argc, char *argv[])
{
    if (argc != 5)
        usageErr("program [dup|dup2] <count> <str of len 2> <file>");

    int count = atoi(argv[2]);
    if (count <= 0)
        errExit("Invalid count %d", count);

    if (strlen(argv[3]) != 2)
        errExit("Invalid str data %s", argv[3]);
    char data1 = argv[3][0];
    char data2 = argv[3][1];
    if (!isalnum(data1) || !isalnum(data2))
        errExit("Invalid data str %s", argv[3]);

    int fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC);
    if (fd < 0)
        errExit("Failed to open %s", argv[4]);

    if (strcmp(argv[1], "dup") == 0)
    {
        int dupfd = dupImpl(fd);
        if (dupfd < 0)
            errExit("Failed to dup.");
        while (count-- > 0)
        {
            if (count % 2 == 0)
            {
                if (write(fd, argv[3], sizeof(char)) != sizeof(char))
                    errExit("Failed to write '%c' to %s", data1, argv[4]);
            }
            else
            {
                if (write(dupfd, argv[3] + 1, sizeof(char)) != sizeof(char))
                    errExit("Failed to write '%c' to %s", data2, argv[4]);
            }
        }
    }
    else if (strcmp(argv[1], "dup2") == 0)
    {
        int dupfd = dup2Impl(fd, 2);
        if (dupfd < 0)
            errExit("Failed to dup.");
        while (count-- > 0)
        {
            if (count % 2 == 0)
            {
                if (write(fd, argv[3], sizeof(char)) != sizeof(char))
                    errExit("Failed to write '%c' to %s", data1, argv[4]);
            }
            else
            {
                if (write(dupfd, argv[3] + 1, sizeof(char)) != sizeof(char))
                    errExit("Failed to write '%c' to %s", data2, argv[4]);
            }
        }
    }
    else
    {
        usageErr("program [dup|dup2] <count> <str of len 2> <file>");
    }

    return 0;
}
