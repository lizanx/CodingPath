#define _POSIX_C_SOURCE 199309
#include <signal.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    if (argc < 4 || strcmp(argv[1], "--help") == 0)
        usageErr("%s <pid> <sig-num> <data> [num-signals]\n", argv[0]);

    printf("%s: PID is %ld, UID is %ld\n", argv[0], (long)getpid(), (long)getuid());

    long sigReceiverPid = getLong(argv[1], 0, "pid");
    int sig = getInt(argv[2], 0, "sig-num");
    int sigData = getInt(argv[3], GN_ANY_BASE, "data");
    int numSigs = (argc > 4) ? getInt(argv[4], GN_GT_0, "num-sigs") : 1;
    union sigval sigVal;
    for (int i = 0; i < numSigs; ++i)
    {
        sigVal.sival_int = sigData + i;
        if (sigqueue(sigReceiverPid, sig, sigVal) == -1)
            errExit("Failed to send sig %d to pid %ld, loop cnt = %d\n",
                    sig, sigReceiverPid, i);
    }

    return 0;
}
