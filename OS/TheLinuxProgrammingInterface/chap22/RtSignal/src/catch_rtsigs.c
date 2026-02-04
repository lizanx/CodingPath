#define _GNU_SOURCE
#include <signal.h>
#include <string.h>
#include "tlpi_hdr.h"

static volatile int g_handlerSleepTime;
static volatile int g_sigCnt;
static volatile int g_allDone;

static void SigInfoHandler(int sig, siginfo_t *sigInfo, void *uctx)
{
    if (sig == SIGINT || sig == SIGTERM)
    {
        g_allDone = 1;
        return;
    }

    ++g_sigCnt;
    printf("caught signal %d\n", sig);
    printf("    si_signo=%d, si_code=%d(%s), ", sigInfo->si_signo, sigInfo->si_code,
           (sigInfo->si_code == SI_USER) ? "SI_USER" : (sigInfo->si_code == SI_QUEUE) ? "SI_QUEUE"
                                                                                      : "other");
    printf("si_value=%d\n", sigInfo->si_value.sival_int);
    printf("    si_pid=%ld, si_uid=%ld\n", (long)sigInfo->si_pid, (long)sigInfo->si_uid);

    sleep(g_handlerSleepTime);
}

int main(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        usageErr("%s [block-time [handler-sleep-time]]\n", argv[0]);

    printf("%s: PID is %ld\n", argv[0], (long)getpid());

    g_handlerSleepTime = (argc > 2) ? getInt(argv[2], GN_NONNEG, "handler-sleep-time") : 1;

    struct sigaction sa;
    sa.sa_sigaction = SigInfoHandler;
    sa.sa_flags = SA_SIGINFO;
    sigfillset(&sa.sa_mask);
    for (int sig = 1; sig < NSIG; ++sig)
        if (sig != SIGTSTP && sig != SIGQUIT)
            sigaction(sig, &sa, NULL);

    if (argc > 1)
    {
        sigset_t blockMask, prevMask;
        sigfillset(&blockMask);
        sigdelset(&blockMask, SIGINT);
        sigdelset(&blockMask, SIGTERM);

        if (sigprocmask(SIG_SETMASK, &blockMask, &prevMask) == -1)
            errExit("Failed to mask signals.");

        printf("%s: signals blocked - sleeping %s seconds\n", argv[0], argv[1]);
        sleep(getInt(argv[1], GN_GT_0, "block-time"));

        if (sigprocmask(SIG_SETMASK, &prevMask, NULL) == -1)
            errExit("Failed to restore signal mask.");
    }

    while (!g_allDone)
    {
        pause();
    }

    return 0;
}
