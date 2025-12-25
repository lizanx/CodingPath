#include <locale.h>
#include <stdio.h>
#include <time.h>
#include "tlpi_hdr.h"

// -> Set TZ env var to change output.
// ls /usr/share/zoneinfo/
// TZ=":<timezone file>" ./build/program

int main(int argc, char *argv[])
{
    // setlocale(LC_ALL, NULL); // -> query only, no side effects.
    // setlocale(LC_ALL, ""); // -> set locale to global locale(env vars like LC_ALL/LC_*/LANG), has side effects.

    char *currentLocale = setlocale(LC_ALL, "");
    if (!currentLocale)
        errExit("Failed to setlocale.");
    printf("Current locale: %s\n\n", currentLocale);

    time_t now = time(NULL);
    printf("ctime() of time() value is: %s\n", ctime(&now));

    struct tm *nowtm = localtime(&now);
    if (!nowtm)
        errExit("Failed to convert time_t to tm.");
    printf("asctime() of local time is: %s\n", asctime(nowtm));

    char buf[256];
    if (strftime(buf, 256, "%A, %d %B %Y, %H:%M:%S %Z", nowtm) == 0)
        errExit("Failed to format local time.");
    printf("strftime() of local time is: %s\n", buf);

    return 0;
}
