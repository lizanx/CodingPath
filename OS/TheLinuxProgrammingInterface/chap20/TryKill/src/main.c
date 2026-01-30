#define _DEFAULT_SOURCE
#include <errno.h>
#include <signal.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s <pid> <SIGINT|SIGTERM|SIGQUIT>\n");

    pid_t pid = getLong(argv[1], 0, "pid");
    int sig = 0;
    if (strcmp(argv[2], "SIGINT") == 0)
        sig = SIGINT;
    else if (strcmp(argv[2], "SIGTERM") == 0)
        sig = SIGTERM;
    else if (strcmp(argv[2], "SIGQUIT") == 0)
        sig = SIGQUIT;
    else
        errExit("Unknown signal %s\n", argv[2]);

    int rc = kill(pid, sig);
    if (sig == 0)
    {
        if (rc == 0)
        {
            printf("Process with pid %d exists and we can send signal to it!\n", pid);
        }
        else
        {
            if (errno == EPERM)
                printf("Process with pid %d exists, but we can't send signal to it!\n", pid);
            else if (errno == ESRCH)
                printf("Process doesn't exist!\n");
            else
                errExit("Call to 'kill' failed with rc = %d", rc);
        }
    }
    else
    {
        if (rc)
            errExit("Call to 'kill' failed with rc %d", rc);
    }

    return 0;
}
