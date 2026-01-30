#define _GNU_SOURCE
#include <signal.h>
#include <string.h>
#include "tlpi_hdr.h"

static int g_signalCount[NSIG];
static volatile sig_atomic_t g_gotSigInt;

static void PrintSigSet(FILE *of, const char *prefix, const sigset_t *sigset)
{
    int cnt = 0;
    for (int sig = 1; sig < NSIG; ++sig)
    {
        if (sigismember(sigset, sig))
        {
            ++cnt;
            fprintf(of, "%s%d (%s)\n", prefix, sig, strsignal(sig));
        }
    }
    if (cnt == 0)
        fprintf(of, "%s<empty sig set>\n", prefix);
}

#if 0
static int PrintPendingSignals(FILE *of, const char *msg)
{
    if (msg)
        fprintf(of, "%s", msg);

    sigset_t sigset;
    if (sigpending(&sigset) == -1)
        return -1;
    PrintSigSet(of, "\t\t", &sigset);

    return 0;
}
#endif

static void SigHandler(int sig)
{
    if (sig == SIGINT)
        g_gotSigInt = 1;
    else
        ++g_signalCount[sig];
}

int main(int argc, char *argv[])
{
    printf("%s: PID is %ld\n", argv[0], (long)getpid());

    for (int n = 1; n < NSIG; ++n)
        signal(n, SigHandler);

    // If a sleep time was specified, temporarily block all signals,
    // sleep(while another process sends us signals), and then
    // display the mask of pending signals and unblock all signals.
    if (argc > 1)
    {
        int sleepSeconds = getInt(argv[1], GN_GT_0, NULL);
        sigset_t pendingMask, blockingMask, emptyMask;
        sigfillset(&blockingMask);
        if (sigprocmask(SIG_SETMASK, &blockingMask, NULL) == -1)
            errExit("Failed to block all signals.");

        printf("%s: sleeping for %d seconds.\n", argv[0], sleepSeconds);
        fflush(stdout);
        sleep(sleepSeconds);

        if (sigpending(&pendingMask) == -1)
            errExit("Failed to get pending signal mask.");
        printf("%s: pending signals are:\n", argv[0]);
        PrintSigSet(stdout, "\t\t", &pendingMask);

        sigemptyset(&emptyMask);
        if (sigprocmask(SIG_SETMASK, &emptyMask, NULL) == -1)
            errExit("Failed to unblock all signals.");
    }

    while (!g_gotSigInt)
    {
        continue;
    }

    for (int n = 1; n < NSIG; ++n)
    {
        if (g_signalCount[n] != 0)
            printf("%s: signal %d caught %d times%s\n",
                   argv[0], n, g_signalCount[n],
                   g_signalCount[n] == 1 ? "" : "s");
    }

    return 0;
}
