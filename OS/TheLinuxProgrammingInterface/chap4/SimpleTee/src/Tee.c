#define _POSIX_C_SOURCE 2
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "tlpi_hdr.h"

#ifndef BUF_SIZE // Allow "-D" option to override buffer size
#define BUF_SIZE 1024
#endif

typedef enum
{
    E_WRITE_OVERRIDE,
    E_WRITE_APPEND
} E_WRITE_MODE;

static E_WRITE_MODE g_write_mode = E_WRITE_OVERRIDE;

// extern int optind;

int main(int argc, char *argv[])
{
    int opt;
    while ((opt = getopt(argc, argv, "a::")) != -1)
    {
        switch (opt)
        {
        case 'a':
            g_write_mode = E_WRITE_APPEND;
            break;
        case '?':
        default:
            usageErr("Unknown option passed, usage: SimpleTee [-a] <output file>");
        }
    }

    if (optind != argc - 1)
        usageErr("Incorrect command format, usage: SimpleTee [-a] <output file>");

    const char *const file = argv[argc - 1];
    int outputOpenFlags = O_WRONLY | O_CREAT;
    if (g_write_mode == E_WRITE_OVERRIDE)
        outputOpenFlags |= O_TRUNC;
    else if (g_write_mode == E_WRITE_APPEND)
        outputOpenFlags |= O_APPEND;
    mode_t outputPermissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; // rw-rw-rw-
    int outputFd = open(file, outputOpenFlags, outputPermissions);
    if (outputFd < 0)
        errExit("Failed to open file %s", file);

    int numRead;
    char buf[BUF_SIZE];
    while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
    {
        if (write(STDOUT_FILENO, buf, numRead) != numRead)
            fatal("Failed to write to stdout.\n");
        if (write(outputFd, buf, numRead) != numRead)
            fatal("Failed to write to output file.\n");
    }

    if (numRead < 0)
        errExit("Read error.\n");

    if (close(outputFd) < 0)
        errExit("Close output");

    return EXIT_SUCCESS;
}
