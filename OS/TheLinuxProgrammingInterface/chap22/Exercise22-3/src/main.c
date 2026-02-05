/*
 * time ./sig_speed_sigsuspend 1000000
 * real    0m32.333s
 * user    0m0.483s
 * sys     0m12.453s
 *
 * time ./build/program 1000000
 * real    0m29.562s
 * user    0m0.317s
 * sys     0m11.457s
 *
 *
 * Codes deleted by "#if 0" are used in "sig_speed_sigsuspend.c".
 */

#define _DEFAULT_SOURCE
#include <signal.h>
#include "tlpi_hdr.h"

#if 0
static void
handler(int sig)
{
}
#endif

#define TESTSIG SIGUSR1

int main(int argc, char *argv[])
{
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s num-sigs\n", argv[0]);

    int numSigs = getInt(argv[1], GN_GT_0, "num-sigs");

#if 0
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if (sigaction(TESTSIG, &sa, NULL) == -1)
        errExit("sigaction");
#endif

    /* Block the signal before fork(), so that the child doesn't manage
       to send it to the parent before the parent is ready to catch it */

    sigset_t blockedMask, emptyMask;
    sigemptyset(&blockedMask);
    sigaddset(&blockedMask, TESTSIG);
    if (sigprocmask(SIG_SETMASK, &blockedMask, NULL) == -1)
        errExit("sigprocmask");

    sigemptyset(&emptyMask);

    // siginfo_t siginfo;
    pid_t childPid = fork();
    switch (childPid)
    {
    case -1:
        errExit("fork");

    case 0: /* child */
        for (int scnt = 0; scnt < numSigs; scnt++)
        {
            if (kill(getppid(), TESTSIG) == -1)
                errExit("kill");
#if 0
            if (sigsuspend(&emptyMask) == -1 && errno != EINTR)
                errExit("sigsuspend");
#else
            int sig = sigwaitinfo(&blockedMask, NULL);
            if (sig != TESTSIG)
                errExit("Unknown sig %d", sig);
#endif
        }
        exit(EXIT_SUCCESS);

    default: /* parent */
        for (int scnt = 0; scnt < numSigs; scnt++)
        {
#if 0
            if (sigsuspend(&emptyMask) == -1 && errno != EINTR)
                errExit("sigsuspend");
#else
            int sig = sigwaitinfo(&blockedMask, NULL);
            if (sig != TESTSIG)
                errExit("Unknown sig %d", sig);
#endif
            if (kill(childPid, TESTSIG) == -1)
                errExit("kill");
        }
        exit(EXIT_SUCCESS);
    }
}
