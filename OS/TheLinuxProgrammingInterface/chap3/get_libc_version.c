#include <gnu/libc-version.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("Glibc version via macros - Major: %d | Minor: %d\n", __GLIBC__, __GLIBC_MINOR__);
    printf("Glibc version via function gnu_get_libc_version(): %s\n", gnu_get_libc_version());
    return 0;
}
