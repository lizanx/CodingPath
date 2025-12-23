#define _GNU_SOURCE
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    malloc_info(0, stdout);

    printf("\n>>>>> <<<<<\n");

    malloc_stats();

    return EXIT_SUCCESS;
}
