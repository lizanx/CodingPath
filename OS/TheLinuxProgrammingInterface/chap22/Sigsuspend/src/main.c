#define _DEFAULT_SOURCE
#include <signal.h>
#include <string.h>
#include <time.h>
#include "signal_functions.h"
#include "tlpi_hdr.h"

static volatile sig_atomic_t g_gotSigQuit;

static void SigHandler(int sig)
{
    printf("Caught signal %d (%s)\n", sig, strsignal(sig));

    if (sig == SIGQUIT)
        g_gotSigQuit = 1;
}

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);

    printSigMask(stdout, "Initial signal mask:\n");

    sigset_t originalMask, blockMask;
    sigemptyset(&blockMask);
    sigaddset(&blockMask, SIGINT);
    sigaddset(&blockMask, SIGQUIT);
    if (sigprocmask(SIG_BLOCK, &blockMask, &originalMask) == -1)
        errExit("sigprocmask - SIG_BLOCK");

    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = SigHandler;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        errExit("Failed to set handler for SIGINT.");
    if (sigaction(SIGQUIT, &sa, NULL) == -1)
        errExit("Failed to set handler for SIGQUIT.");

    for (int i = 1; !g_gotSigQuit; ++i)
    {
        printf("=== LOOP %d\n", i);

        printSigMask(stdout, "Starting critical section, signal mask is:\n");
        for (time_t start = time(NULL); time(NULL) < start + 4;) // Simulate critical section
            continue;

        printPendingSigs(stdout, "Before sigsuspend() - pending signals:\n");
        if (sigsuspend(&originalMask) == -1 && errno != EINTR)
            errExit("sigsuspend");
    }

    if (sigprocmask(SIG_SETMASK, &originalMask, NULL) == -1)
        errExit("Failed to restore signal mask.");

    printSigMask(stdout, "=== Exited loop\nRestore signal mask to:\n");

    return 0;
}
