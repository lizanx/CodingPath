#define _XOPEN_SOURCE 700
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "tlpi_hdr.h"

typedef enum
{
    OP_READ,
    OP_WRITE,
} EOperations;

typedef struct
{
    int fd;
    EOperations operation;
    off_t offset;
    void *buf;
    size_t size;
} ThreadArgs;

static void *ThreadFn(void *args)
{
    sleep(1);

    ThreadArgs *targs = (ThreadArgs *)args;
    if (targs->operation == OP_READ)
    {
        ssize_t cnt = pread(targs->fd, targs->buf, targs->size, targs->offset);
        if (cnt < 0)
            errExit("Failed to read.");
        if (cnt != targs->size)
            printf("Only read %zd at offset %ld\n", cnt, targs->offset);
        char *buf = malloc(targs->size + 1);
        memcpy(buf, targs->buf, targs->size);
        buf[targs->size] = '\0';
        printf("Read content: %s\n", buf);
        free(buf);
    }
    else if (targs->operation == OP_WRITE)
    {
        ssize_t cnt = pwrite(targs->fd, targs->buf, targs->size, targs->offset);
        if (cnt < 0)
            errExit("Failed to write.");
        if (cnt != targs->size)
            printf("Only write %zd at offset %ld\n", cnt, targs->offset);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    int fd = open("./data.txt", O_RDWR);
    if (fd < 0)
        errExit("Failed to open data file.");

    char buf[16];
    strcpy(buf, "AAAAABBBBBCCCCC");
    ThreadArgs arg1 = {
        .fd = fd,
        .operation = OP_READ,
        .offset = 3,
        .buf = buf,
        .size = 5};
    ThreadArgs arg2 = {
        .fd = fd,
        .operation = OP_WRITE,
        .offset = 10,
        .buf = buf + 5,
        .size = 5};
    ThreadArgs arg3 = {
        .fd = fd,
        .operation = OP_WRITE,
        .offset = 20,
        .buf = buf + 10,
        .size = 5};
    pthread_t t1, t2, t3;
    if (pthread_create(&t1, NULL, ThreadFn, &arg1) != 0)
        errExit("Failed to create thread 1.");
    if (pthread_create(&t2, NULL, ThreadFn, &arg2) != 0)
        errExit("Failed to create thread 2.");
    if (pthread_create(&t3, NULL, ThreadFn, &arg3) != 0)
        errExit("Failed to create thread 3.");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
}
