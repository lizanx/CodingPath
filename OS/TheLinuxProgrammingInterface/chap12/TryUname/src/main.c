#include <stdio.h>
#include <sys/utsname.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    struct utsname uts;

    if (uname(&uts) < 0)
        errExit("Failed to get utsname.");

    printf("Sysname: %s\n", uts.sysname);
    printf("Version: %s\n", uts.version);
    printf("Release: %s\n", uts.release);
    printf("Machine: %s\n", uts.machine);
    printf("Node name: %s\n", uts.nodename);

    return 0;
}
