#include <fcntl.h>
#include <sys/stat.h>
#include "tlpi_hdr.h"

#define CMD_SIZE 128
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("program <temp file> [number of 1KiB blocks]");

    const char *file = argv[1];
    int blkCnt = (argc > 2) ? getInt(argv[2], GN_GT_0, "num-1KB-blocks") : 10000;
    char shellCmd[CMD_SIZE];
    char buffer[BUFSIZ];

    int fd = open(file, O_CREAT | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR);
    if (fd < 0)
        errExit("Failed to create %s", file);
    if (unlink(file))
        errExit("Failed to unlink %s", file);

    snprintf(shellCmd, CMD_SIZE, "df -k `dirname %s`", file);
    printf("===== Before writing to unlinked file =====\n");
    system(shellCmd);

    for (int i = 0; i < blkCnt; ++i)
        if (write(fd, buffer, BUFSIZ) != BUFSIZ)
            errExit("Failed to write to %s", file);
    printf("===== After writing to unlinked file =====\n");
    system(shellCmd);

    if (close(fd))
        errExit("Failed to close %s", file);
    printf("===== After closing unlinked file =====\n");
    system(shellCmd);

    return 0;
}
