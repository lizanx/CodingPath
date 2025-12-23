#define _DEFAULT_SOURCE
#include <stdio.h>
#include <unistd.h>
#include "tlpi_hdr.h"

static void ShowProgramBreak()
{
    void *programBreak = sbrk(0);
    if (programBreak == (void *)-1)
        errExit("Failed to call sbrk.");
    printf("Program break at %p\n", programBreak);
}

// Due to the internal implementation details of libc,
// the memory may be allocated on heap for caching/pre-allocation.
// Therefore, the results in output may be a surprise.
int main(int argc, char *argv[])
{
    ShowProgramBreak();

    printf("Allocating memory on stack..\n");
    ShowProgramBreak();
    char *buf = alloca(32);
    if (!buf)
        errExit("Failed to allocate memory on stack.");
    ShowProgramBreak();

    printf("Allocating memory on heap..\n");
    ShowProgramBreak();
    buf = malloc(32);
    if (!buf)
        errExit("Failed to allocate memory on heap.");
    ShowProgramBreak();
    free(buf);

    return EXIT_SUCCESS;
}