#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>

static const size_t MEM_CHUNK_SIZE = 1024;

int main(int argc, char *argv[])
{
    mtrace();

    for (int i = 0; i < 8; ++i)
    {
        void *alloc_mem = malloc(MEM_CHUNK_SIZE);
        if (!alloc_mem)
        {
            printf("[Round-%d]Failed to allocate memory.\n", i);
            continue;
        }
        printf("[Round-%d]Memory allocated at %p\n", i, alloc_mem);
        // Only free memory in even rounds to simulate memory leak.
        if (i % 2 == 0)
            free(alloc_mem);
    }

    exit(EXIT_SUCCESS);
}
