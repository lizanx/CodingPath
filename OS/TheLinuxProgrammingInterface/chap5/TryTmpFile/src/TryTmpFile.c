#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    char template[] = "/tmp/gavin-tmp-XXXXXX";
    int fd = mkstemp(template);
    if (fd < 0)
        errExit("Failed to create tmp %s", template);
    printf("%s successfully created!\n", template);
    write(fd, template, sizeof(template));
    lseek(fd, 0, SEEK_SET);
    char buf1[sizeof(template)];
    read(fd, buf1, sizeof(buf1));
    printf("Read back content: '%s'\n", buf1);
    close(fd);

    FILE *file = tmpfile();
    if (!file)
        errExit("Failed to create tmp file via 'tmpfile()'");
    fprintf(file, "template : %s", template);
    fseek(file, 0, SEEK_SET);
    char buf2[64];
    size_t readCnt = fread(buf2, sizeof(*buf2), sizeof(buf2) - 1, file);
    buf2[readCnt] = '\0';
    printf("Read back content: '%s'\n", buf2);

    return EXIT_SUCCESS;
}
