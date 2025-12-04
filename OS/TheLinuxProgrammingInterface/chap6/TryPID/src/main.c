#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "tlpi_hdr.h"

extern char etext, edata, end;

int main(int argc, char *argv[])
{
    pid_t currPID = getpid();
    pid_t parentPID = getppid();
    printf("Current PID: %d, parent PID: %d\n", currPID, parentPID);

    printf("======== Address of program segments ========\n");
    printf("Text segment ends at %p\n", &etext);
    printf("Data segment ends at %p\n", &edata);
    printf("BSS segment ends at %p\n", &end);

    printf("\n======== Cmd args ========\n");
    // Method 1
    for (int i = 0; i < argc; ++i)
        printf("Argument: '%s'\n", argv[i]);
    // Method 2
    for (char **p = argv; *p != NULL; ++p)
        printf("_Argument: '%s'\n", *p);
    // Method 3 - non-portable
    int fd = open("/proc/self/cmdline", O_RDONLY);
    if (fd < 0)
        errExit("Failed to open /proc/self/cmdline.");
    char buf[128];
    if (read(fd, buf, sizeof(buf)) < 0)
        errExit("Failed to read.");
    for (char *p = buf; *p != '\0' && p < buf + sizeof(buf); p += strlen(p) + 1)
    {
        printf("__Argument: '%s'\n", p);
    }
    if (close(fd) < 0)
        errExit("Failed to close.");
    // Method 4 - non-portable
    printf("___Argument[0]: '%s' at '%s'\n", program_invocation_short_name, program_invocation_name);

    return 0;
}
