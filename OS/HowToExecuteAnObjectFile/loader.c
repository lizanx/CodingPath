#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <elf.h>
#include <errno.h>

typedef union
{
    const Elf64_Ehdr *hdr;
    const uint8_t *base;
} objhdr;

static void load_obj(void)
{
    // Load obj.o into memory.
}

static void parse_obj(void)
{
    // Parse an object file and find 'add5' and 'add10' functions.
}

static void execute_funcs(void)
{
    // Execute 'add5' and 'add10' with some inputs.
}

int main(void)
{
    load_obj();
    parse_obj();
    execute_funcs();

    return EXIT_SUCCESS;
}
