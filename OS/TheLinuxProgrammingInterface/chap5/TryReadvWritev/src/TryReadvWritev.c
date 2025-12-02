#include <fcntl.h>
#include <sys/uio.h>
#include <stdio.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    int fd = open("./data.txt", O_RDWR);
    if (fd < 0)
        errExit("Failed to open data file.");

    char readBuf[65] = {'\0'};
    struct iovec readVecs[2] = {
        [0] = {
            .iov_base = readBuf,
            .iov_len = 32,
        },
        [1] = {
            .iov_base = readBuf + 32,
            .iov_len = 32,
        }};
    ssize_t readCnt = readv(fd, readVecs, 2);
    if (readCnt < 0)
        errExit("Failed to readv.");
    if (readCnt != sizeof(readBuf) - 1)
        printf("Only read %ld bytes(<%zu)\n", readCnt, sizeof(readBuf));
    printf("Read content: %s\n", readBuf);

    lseek(fd, 0, SEEK_SET);
    char writeBuf[32];
    memcpy(writeBuf, "AAAAAAAABBBBBBBBCCCCCCCCDDDDDDDD", sizeof(writeBuf));
    struct iovec writeVecs[3] =
        {
            [0] = {
                .iov_base = writeBuf,
                .iov_len = 10,
            },
            [1] = {
                .iov_base = writeBuf + 10,
                .iov_len = 8,
            },
            [2] = {
                .iov_base = writeBuf + 10 + 8,
                .iov_len = 32 - 10 - 8,
            }};
    ssize_t writeCnt = writev(fd, writeVecs, 3);
    if (writeCnt < 0)
        errExit("Failed to writev.");
    if (writeCnt != sizeof(writeBuf))
        printf("Only write %ld bytes(<%zu)\n", writeCnt, sizeof(writeBuf));

    close(fd);
    return 0;
}
