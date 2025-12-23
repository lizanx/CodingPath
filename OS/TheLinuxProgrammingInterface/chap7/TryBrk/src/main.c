#define _DEFAULT_SOURCE
#include <stdio.h>
#include <unistd.h>
#include "tlpi_hdr.h"

#define MAX_ALLOC_CNT 1000000

static char *memory[MAX_ALLOC_CNT] = {
    NULL,
};

int main(int argc, char *argv[])
{
    int numAllocs, blockSize, freeStep, freeMin, freeMax;

    if (argc < 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s <n blocks> <block size> [step [min [max]]]\n", argv[0]);

    numAllocs = getInt(argv[1], GN_GT_0, "number of allocs");
    if (numAllocs > MAX_ALLOC_CNT)
        cmdLineErr("num-allocs > %d\n", MAX_ALLOC_CNT);

    blockSize = getInt(argv[2], GN_GT_0, "block size");
    freeStep = argc > 3 ? getInt(argv[3], GN_GT_0, "free step") : 1;
    freeMin = argc > 4 ? getInt(argv[4], GN_GT_0, "min") : 1;
    freeMax = argc > 5 ? getInt(argv[5], GN_GT_0, "max") : numAllocs;
    if (freeMax > numAllocs)
        cmdLineErr("free-max > num-allocs\n");

    printf("Initial program break: %p\n", sbrk(0));
    printf("Adjusting %d * %d bytes\n", numAllocs, blockSize);
    for (int i = 0; i < numAllocs; ++i)
    {
        memory[i] = malloc(blockSize);
        if (!memory[i])
            errExit("Failed to allocate %dbytes for %d-th block.", blockSize, i);
    }
    printf("Program break now: %p\n", sbrk(0));

    printf("Freeing memory blocks from %d to %d of step %d\n", freeMin, freeMax, freeStep);
    for (int i = freeMin - 1; i < freeMax; i += freeStep)
    {
        free(memory[i]);
        memory[i] = NULL;
    }
    printf("After free(), program break now: %p\n", sbrk(0));

    return EXIT_SUCCESS;
}
