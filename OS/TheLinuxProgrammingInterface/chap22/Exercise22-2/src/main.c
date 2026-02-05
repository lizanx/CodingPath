#define _DEFAULT_SOURCE
#include <signal.h>
#include <string.h>
#include "tlpi_hdr.h"

static void Handler(int sig)
{
    printf("Received signal %d(%s)\n", sig, strsignal(sig));
}

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("%s: PID is %ld, SIGRTMIN = %d, SIGRTMAX = %d\n",
           argv[0], (long)getpid(), SIGRTMIN, SIGRTMAX);

    sigset_t mask, originalMask;
    sigfillset(&mask);
    sigdelset(&mask, SIGQUIT);
    if (sigprocmask(SIG_SETMASK, &mask, &originalMask) == -1)
        errExit("Failed to set proc mask.");

    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = Handler;
    sigfillset(&sa.sa_mask);
    for (int sig = 1; sig < NSIG; ++sig)
    {
        if (sigaction(sig, &sa, NULL) == -1)
            printf("Failed to set handler for signal %d(%s)\n", sig, strsignal(sig));
    }

    printf("%s: sleep for 60s...\n", argv[0]);
    sleep(60);

    printf("%s: wake up, unmask signals.\n", argv[0]);
    if (sigprocmask(SIG_SETMASK, &originalMask, NULL) == -1)
        errExit("Failed to restore proc mask.");

    sigemptyset(&mask);
    for (;;)
    {
        sigpending(&mask);
        int hasPendingSignal = 0;
        for (int sig = 1; sig < NSIG; ++sig)
        {
            if (sigismember(&mask, sig))
            {
                hasPendingSignal = 1;
                break;
            }
        }
        if (!hasPendingSignal)
            break;
    }

    printf("%s: exit program\n", argv[0]);

    return 0;
}
