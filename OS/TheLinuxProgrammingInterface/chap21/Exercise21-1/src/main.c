#define _DEFAULT_SOURCE
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "tlpi_hdr.h"

static void AbortImpl()
{
    // If user sets customized handler, trigger it.
    raise(SIGABRT);

    // Restore handler of abort signal to default(terminate and core dump).
    struct sigaction sa =
        {
            .sa_flags = 0,
            .sa_handler = SIG_DFL};
    sigemptyset(&sa.sa_mask);
    sigaction(SIGABRT, &sa, NULL);

    // Send the signal again, which should always terminate the program.
    raise(SIGABRT);

    // Last guard, exit directly if the signal is blocked.
    _exit(127);
}

int main(int argc, char *argv[])
{
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s [1|2]\n", argv[0]);

    setvbuf(stdout, NULL, _IONBF, 0);

    if (strcmp(argv[1], "1") == 0)
    {
        printf("Glibc version of 'abort'.\n");
        abort();
    }
    else if (strcmp(argv[1], "2") == 0)
    {
        printf("Customized version of 'abort'.\n");
        AbortImpl();
    }

    printf("Program exit.\n");

    return 0;
}
