#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#ifndef BUF_SIZE // Allow "-D" option to override buffer size
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[])
{
    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s <old file> <new file>\n", argv[0]);

    int inputFd = open(argv[1], O_RDONLY);
    if (inputFd < 0)
        errExit("Open file %s", argv[1]);

    int outputOpenFlags = O_WRONLY | O_CREAT | O_TRUNC;
    mode_t outputPermissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; // rw-rw-rw-
    int outputFd = open(argv[2], outputOpenFlags, outputPermissions);
    if (outputFd < 0)
    {
        errExit("Open file %s", argv[2]);
    }

    int numRead;
    char buf[BUF_SIZE];
    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
    {
        if (write(outputFd, buf, numRead) != numRead)
            fatal("Couldn't write whole buffer.");
    }

    if (numRead < 0)
        errExit("Read\n");

    if (close(inputFd) < 0)
        errExit("Close input");
    if (close(outputFd) < 0)
        errExit("Close output");

    return EXIT_SUCCESS;
}
