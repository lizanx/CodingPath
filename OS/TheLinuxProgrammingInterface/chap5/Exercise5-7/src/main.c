#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/uio.h>
#include "tlpi_hdr.h"

static ssize_t readvImpl(int fd, const struct iovec *iov, int iovcnt)
{
    if (!iov || iovcnt <= 0)
        return 0;

    ssize_t totalCnt = 0;
    for (int i = 0; i < iovcnt; ++i)
    {
        ssize_t cnt = read(fd, iov[i].iov_base, iov[i].iov_len);
        if (cnt < 0)
        {
            fprintf(stderr, "Failed to read int %d-th iovec.\n", i);
            return -1;
        }
        totalCnt += cnt;
        if (cnt < iov[i].iov_len)
            break;
    }

    return totalCnt;
}

static ssize_t writevImpl(int fd, const struct iovec *iov, int iovcnt)
{
    if (!iov || iovcnt <= 0)
        return 0;

    size_t totalLength = 0;
    for (int i = 0; i < iovcnt; ++i)
        totalLength += iov[i].iov_len;
    char *buf = malloc(totalLength);
    if (!buf)
    {
        fprintf(stderr, "Failed to allocate buffer of size %zu.\n", totalLength);
        return -1;
    }
    size_t offset = 0;
    for (int i = 0; i < iovcnt; ++i)
    {
        memcpy(buf + offset, iov[i].iov_base, iov[i].iov_len);
        offset += iov[i].iov_len;
    }
    ssize_t cnt = write(fd, buf, totalLength);
    if (cnt < 0)
    {
        fprintf(stderr, "Failed to write.\n");
        return -1;
    }
    return cnt;
}

static char g_writeStr[] = "Hello world! The Linux Programming Interface";
static char g_readStr[sizeof(g_writeStr)];

int main(int argc, char *argv[])
{
    if (argc != 2)
        usageErr("program <file>");
    const char *const file = argv[1];
    int fd = open(file, O_CREAT | O_RDWR | O_TRUNC);
    if (fd < 0)
        errExit("Failed to open %s", file);

    struct iovec iov[3];
    iov[0].iov_base = g_writeStr;
    iov[0].iov_len = 5;
    iov[1].iov_base = g_writeStr + 5;
    iov[1].iov_len = 8;
    iov[2].iov_base = g_writeStr + 5 + 8;
    iov[2].iov_len = 31;
    ssize_t cnt = writevImpl(fd, iov, 3);
    if (cnt != 5 + 8 + 31)
        errExit("Failed to writevImpl");

    if (lseek(fd, 0, SEEK_SET) != 0)
        errExit("Failed to lseek.");

    iov[0].iov_base = g_readStr;
    iov[0].iov_len = 12;
    iov[1].iov_base = g_readStr + 12;
    iov[1].iov_len = 10;
    iov[2].iov_base = g_readStr + 12 + 10;
    iov[2].iov_len = 22;
    cnt = readvImpl(fd, iov, 3);
    if (cnt != 12 + 10 + 22)
        errExit("Failed to readvImpl.");
    g_readStr[sizeof(g_readStr) - 1] = '\0';
    fprintf(stdout, "Content read: '%s'\n", g_readStr);

    if (close(fd) < 0)
        errExit("Failed to close %s", file);
    return 0;
}
