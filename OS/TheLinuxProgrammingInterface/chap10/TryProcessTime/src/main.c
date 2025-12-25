#define _DEFAULT_SOURCE
#include <stdio.h>
#include <sys/times.h>
#include <time.h>
#include "tlpi_hdr.h"

static void DisplayProcessTime(const char *msg)
{
    static long clockTicks;

    if (!clockTicks)
    {
        clockTicks = sysconf(_SC_CLK_TCK);
        if (clockTicks < 0)
            errExit("Failed to get clock ticks.");
    }

    if (msg)
        printf("%s", msg);

    clock_t clks = clock();
    if (clks < 0)
        errExit("Failed to get clocks by clock()");
    printf("\tclock() returns: %ld clocks, %.2lf secs(%ld clocks per second)\n",
           clks, (double)clks / CLOCKS_PER_SEC, CLOCKS_PER_SEC);

    struct tms t;
    if (times(&t) < 0)
        errExit("Failed to get tms by times().");
    printf("\ttimes() yields: user cpu %.2lf secs, sys cpu %.2lf secs\n",
           (double)t.tms_utime / clockTicks,
           (double)t.tms_stime / clockTicks);
}

int main(int argc, char *argv[])
{
    int loopCnt = 10000000;
    if (argc == 2)
        loopCnt = getInt(argv[1], GN_GT_0, "num-calls");
    printf("Loop cnt: %d\n", loopCnt);

    DisplayProcessTime("Before loop:\n");

    for (int i = 0; i < loopCnt; ++i)
    {
        (void)getpid();
        (void)getppid();
    }

    DisplayProcessTime("After loop:\n");

    return 0;
}
