#define _GNU_SOURCE
#include <string.h>
#include <signal.h>
#include <sys/signalfd.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s <sig-num...>\n", argv[0]);

    printf("%s: PID is %ld\n", argv[0], (long)getpid());

    sigset_t sigMask;
    sigemptyset(&sigMask);
    for (int i = 1; i < argc; ++i)
        if (sigaddset(&sigMask, atoi(argv[1])))
            errExit("%s: failed to add %d to mask.", argv[0], atoi(argv[i]));

    if (sigprocmask(SIG_BLOCK, &sigMask, NULL) == -1)
        errExit("%s: failed to block signals.", argv[0]);

    int sigFd = signalfd(-1, &sigMask, 0);
    if (sigFd == -1)
        errExit("%s: failed to call signalfd.", argv[0]);

    struct signalfd_siginfo sigfdInfo;
    for (;;)
    {
        ssize_t sz = read(sigFd, &sigfdInfo, sizeof(sigfdInfo));
        if (sz != sizeof(sigfdInfo))
            errExit("%s: failed to read from sigfd.", argv[0]);

        printf("%s: got signal %d(%s)", argv[0], sigfdInfo.ssi_signo, strsignal(sigfdInfo.ssi_signo));
        if (sigfdInfo.ssi_code == SI_QUEUE)
        {
            printf("; ssi_pid = %ld; ssi_int = %d", (long)sigfdInfo.ssi_pid, sigfdInfo.ssi_int);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}
