#define _DEFAULT_SOURCE
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    time_t t = time(NULL);
    printf("Current time: %s\n", ctime(&t));

    struct timeval tv;
    if (gettimeofday(&tv, NULL) < 0)
        errExit("Failed to get time of day.");
    printf("Time value: %ld seconds, %ld useconds.\n", tv.tv_sec, tv.tv_usec);

    struct tm tmUtc, tmLocal;
    struct tm *ptm;
    if ((ptm = gmtime(&t)) == NULL)
        errExit("Failed to convert time_t to struct tm(UTC).");
    tmUtc = *ptm;
    printf("Current time(UTC): %s\n", asctime(&tmUtc));
    if ((ptm = localtime(&t)) == NULL)
        errExit("Failed to convert time_t to struct tm(local).");
    tmLocal = *ptm;
    printf("Current time(Local): %s\n", asctime(&tmLocal));

    time_t t2 = mktime(&tmLocal);
    if (t2 != t)
        errExit("Original t and converted back t2 unmatch.");

    return 0;
}
