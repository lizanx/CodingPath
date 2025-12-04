#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "tlpi_hdr.h"

#define FILE "./tmp.txt"
static const char originalContent[] = "This is some random original text.";
static const char newContent[] = "Hello world!";

int main(int argc, char *argv[])
{
    // Write some content to the file in advance.
    int fd = open(FILE, O_CREAT | O_WRONLY | O_TRUNC);
    if (fd < 0)
        errExit("Failed to open %s", FILE);
    ssize_t writeCnt = write(fd, originalContent, strlen(originalContent));
    if (writeCnt < 0 || writeCnt != strlen(originalContent))
        errExit("Failed to write to %s", FILE);
    close(fd);

    // Check the behavior of write+O_APPEND.
    // Result: even if you seek to begin of the file, since it's opened with O_APPEND, any writes still append to the tail.
    fd = open(FILE, O_WRONLY | O_APPEND);
    if (fd < 0)
        errExit("Failed to open %s", FILE);
    off_t offset = lseek(fd, 0, SEEK_SET);
    if (offset < 0)
        errExit("Failed to lseek.");
    printf("Offset set to %ld\n", offset);
    writeCnt = write(fd, newContent, strlen(newContent));
    if (writeCnt < 0 || writeCnt != strlen(newContent))
        errExit("Failed to write to %s", FILE);
    close(fd);

    return 0;
}
