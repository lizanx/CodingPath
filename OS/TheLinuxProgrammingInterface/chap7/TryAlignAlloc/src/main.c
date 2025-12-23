#define _GNU_SOURCE
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *buf1 = memalign(1024, 4096);
    if (buf1)
    {
        printf("buf1 allocated via memalign at %p\n", buf1);
    }
    else
    {
        printf("Failed to  allocate via memallign\n");
    }

    char *buf2 = NULL;
    if (!posix_memalign((void **)(&buf2), 1024, 4096))
    {
        printf("buf2 allocated via posix_memalign at %p\n", buf2);
    }
    else
    {
        printf("Failed to allocate via posix_memalign\n");
    }

    free(buf1);
    free(buf2);

    return EXIT_SUCCESS;
}
