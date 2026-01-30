#define _DEFAULT_SOURCE
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "tlpi_hdr.h"

// extern const char *const sys_siglist[]; // #define _BSD_SOURCE

static void SigHandler(int sig)
{
    if (sig == SIGINT)
    {
        printf("Ouch! SIGINT received.\n");
        return;
    }
    printf("SIGQUIT received, quit now!\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Description for SIGINT:\n");
    // printf("\t%s\n", sys_siglist[SIGINT]);
    printf("\t%s\n", strsignal(SIGINT));
    psignal(SIGINT, "\tpsignal");
    printf("Description for SIGQUIT:\n");
    // printf("\t%s\n", sys_siglist[SIGQUIT]);
    printf("\t%s\n", strsignal(SIGQUIT));
    psignal(SIGQUIT, "\tpsignal");

    if (signal(SIGINT, SigHandler) == SIG_ERR)
        errExit("Failed to set sig handler for SIGINT.");
    if (signal(SIGQUIT, SigHandler) == SIG_ERR)
        errExit("Failed to set sig handler for SIGQUIT.");

    for (;;)
    {
        pause();
        // Action of 'signal' differs on SystemV/BSD, where the former by default
        // sets the signal handler to SIG_DFT after signal handler is triggered.
        // On Linux, glibc by default follows the behavior of System V 'signal' convention.
        // Therefore, we set the sig handler again each time after waking from 'pause'.
        if (signal(SIGINT, SigHandler) == SIG_ERR)
            errExit("Failed to set sig handler for SIGINT.");
    }

    return 0;
}
