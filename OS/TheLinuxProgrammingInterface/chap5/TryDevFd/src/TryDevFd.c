#include <fcntl.h>
#include <stdio.h>
#include "tlpi_hdr.h"

const char g_msg1[] = "Hello world.\n";
const char g_msg2[] = "'The Linux Programming Interface' is a detailed book.\n";
const char g_msg3[] = "Fedora Linux.\n";

int main(int argc, char *argv[])
{
    if (argc != 3)
        usageErr("TryDevFd <data file 1> <data file 2>");

    const char *file1 = argv[1];
    const char *file2 = argv[2];

    // Two "open" on the same file, two descriptor table entries, offset not shared.
    int fd1 = open(file1, O_CREAT | O_TRUNC | O_WRONLY);
    if (fd1 < 0)
        errExit("Failed to open %s.", file1);
    int fd1Dup = open(file1, O_WRONLY);
    if (fd1Dup < 0)
        errExit("Failed to open %s again.", file1);
    // The "write" calls will override each other.
    if (write(fd1, g_msg2, sizeof(g_msg2)) < 0)
        errExit("Failed to write to %s.", file2);
    if (write(fd1Dup, g_msg1, sizeof(g_msg1)) < 0)
        errExit("Failed to write to %s again.", file1);
    if (close(fd1Dup) < 0)
        errExit("Failed to close duplicated %d", fd1Dup);
    if (close(fd1) < 0)
        errExit("Failed to close %d", fd1);

    // !!!! Opening "/dev/fd/xx" will share the same file descriptor table entry, just like "dup".  ---> ERROR!! Not for regular file!!!! Only for stdin/stdout/stderr/pipe/socket..
    int fd2 = open(file2, O_CREAT | O_TRUNC | O_WRONLY);
    if (fd2 < 0)
        errExit("Failed to open %s.", file2);
    char filePath[32] = {'\0'};
    if (snprintf(filePath, sizeof(filePath), "/dev/fd/%d", fd2) < 0)
        errExit("Failed to format /dev/fd/ file path.");
    printf("Opening file at %s", filePath);
    // !!!!! Cannot use O_CREAT/O_TRUNC here, otherwise the fd table entry is not shared !!!!!
    int fd2Dup = open(filePath, O_WRONLY);
    if (fd2Dup < 0)
        errExit("Failed to open %s.", filePath);
    // The "write" calls share the same system-file struct(sharing offset), thus no override occurs.
    if (write(fd2, g_msg1, sizeof(g_msg1)) < 0)
        errExit("Failed to write to %s.", file2);
    if (write(fd2Dup, g_msg2, sizeof(g_msg2)) < 0)
        errExit("Failed to write to %s.", filePath);
    if (write(fd2, g_msg3, sizeof(g_msg3)) < 0)
        errExit("Failed to write to %s.", file2);
    if (close(fd2Dup) < 0)
        errExit("Failed to close duplicated %d", fd2Dup);
    if (close(fd2) < 0)
        errExit("Failed to close %d", fd2);

    return 0;
}
