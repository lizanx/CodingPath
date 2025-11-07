#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
#ifdef _POSIX_SOURCE
    printf("_POSIX_SOURCE defined\n"); // defined by default
#endif
#ifdef _POSIX_C_SOURCE
    printf("_POSIX_C_SOURCE defined: %d\n", _POSIX_C_SOURCE); // defined as "200809" by default
#endif
#ifdef _XOPEN_SOURCE
    printf("_XOPEN_SOURCE defined: %d\n", _XOPEN_SOURCE);
#endif
#ifdef _BSD_SOURCE
    printf("_BSD_SOURCE defined\n");
#endif
#ifdef _SVID_SOURCE
    printf("_SVID_SOURCE defined\n");
#endif
#ifdef _GNU_SOURCE
    printf("_GNU_SOURCE defined\n");
#endif
}
