#include <stdio.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    printf("Hello, copy!\n");
    printf("argc: %d, argv[0]: %s\n", argc, argv[0]);
    usageErr("Fake error.\n");

    return 0;
}
