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

    printf("%s: PID is %ld\n", argv[0], (long)getpid());

    struct sigaction sa;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGCONT);
    sa.sa_handler = Handler;
    if (sigaction(SIGCONT, &sa, NULL) == -1)
        errExit("Failed to set signal handler");

    sigset_t mask, originalMask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGCONT);
    if (sigprocmask(SIG_SETMASK, &mask, &originalMask) == -1)
        errExit("Failed to set process mask.");

    for (int i = 0; i < 3; ++i)
    {
        pause();
        printf("%s: wake up, i = %d\n", argv[0], i);
    }
    printf("%s: exit loop.\n", argv[0]);

    if (sigprocmask(SIG_SETMASK, &originalMask, NULL) == -1)
        errExit("Failed to set process mask.");
    sleep(1);

    return 0;
}
