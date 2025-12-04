#include <fcntl.h>
#include <unistd.h>
#include "tlpi_hdr.h"

static const char g_data[1] = {'x'};

int main(int argc, char *argv[])
{
    if (argc != 3 && argc != 4)
        usageErr("program <file name> <num of bytes> [x]");

    int appendMode = 1;
    if (argc == 4 && strcmp(argv[3], "x") == 0)
        appendMode = 0;

    long numBytes = atol(argv[2]);
    if (numBytes <= 0)
        errExit("Invalid bytes count: %s", argv[2]);

    int flags = O_CREAT | O_WRONLY;
    if (appendMode)
        flags |= O_APPEND;
    int fd = open(argv[1], flags);
    if (fd < 0)
        errExit("Failed to open %s", argv[1]);
    while (numBytes-- > 0)
    {
        if (appendMode)
        {
            if (write(fd, g_data, sizeof(g_data)) <= 0)
                errExit("Failed to write.");
        }
        else
        {
            // Without 'O_APPEND' flag, after seeking and before writing, another process may have written a new byte.
            // Thus the byte to write may override the byte written by another process.
            // Namely two processes mean to write 2 bytes in total, but in actual only 1 byte is written at the same position twice.
            if (lseek(fd, 0, SEEK_END) < 0)
                errExit("Failed to seek to end.");
            if (write(fd, g_data, sizeof(g_data)) <= 0)
                errExit("Failed to write.");
        }
    }

    if (close(fd) < 0)
        errExit("Failed to close %s", argv[1]);
    return 0;
}
