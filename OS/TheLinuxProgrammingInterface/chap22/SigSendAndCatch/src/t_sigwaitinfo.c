#define _GNU_SOURCE
#include <signal.h>
#include <string.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        usageErr("%s [delay-seconds]\n", argv[0]);

    printf("%s: PID is %ld\n", argv[0], (long)getpid());

    sigset_t sigSet;
    sigfillset(&sigSet);
    if (sigprocmask(SIG_SETMASK, &sigSet, NULL) == -1)
        errExit("Failed to block signals.");
    printf("%s: signals blocked.\n", argv[0]);

    if (argc > 1)
    {
        int sleepSeconds = getInt(argv[1], GN_GT_0, "delay-seconds");
        printf("%s: about to delay %d seconds.\n", argv[0], sleepSeconds);
        sleep(sleepSeconds);
    }

    siginfo_t sigInfo;
    for (;;)
    {
        int sig = sigwaitinfo(&sigSet, &sigInfo);
        if (sig == -1)
            errExit("Failed to wait sig info.");

        if (sig == SIGINT || sig == SIGTERM)
            exit(EXIT_SUCCESS);

        printf("Got signal %d (%s)\n", sig, strsignal(sig));
        printf("\tsi_signo = %d, si_code = %d(%s)", sigInfo.si_signo, sigInfo.si_code,
               (sigInfo.si_code == SI_USER)    ? "SI_USER"
               : (sigInfo.si_code == SI_QUEUE) ? "SI_QUEUE"
                                               : "Other");
        if (sigInfo.si_code == SI_QUEUE)
            printf(", si_value = %d\n", sigInfo.si_value.sival_int);
        else
            printf("\n");
        printf("\tsi_pid = %ld, si_uid = %ld\n", (long)sigInfo.si_pid, (long)sigInfo.si_uid);
    }

    return EXIT_SUCCESS;
}
