#define _DEFAULT_SOURCE
#include <signal.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    if (argc < 4 || strcmp(argv[1], "--help") == 0)
        usageErr("%s pid num-sigs sig-num [sig-num-2]\n", argv[0]);

    pid_t pid = getLong(argv[1], 0, "PID");
    int numOfSigs = getInt(argv[2], GN_GT_0, "number-of-signals");
    int sig = getInt(argv[3], 0, "sig-num");

    printf("%s: sending signal %d to process %d for %d times.\n", argv[0], sig, pid, numOfSigs);

    for (int i = 0; i < numOfSigs; ++i)
        if (kill(pid, sig) == -1)
            errExit("Failed to send %d-th sig %d", i, sig);

    if (argc > 4)
    {
        int sig2 = getInt(argv[4], 0, "sig-num-2");
        if (kill(pid, sig2) == -1)
            errExit("Failed to send sig2 %d", sig2);
    }

    printf("%s exiting\n", argv[0]);
    return 0;
}
