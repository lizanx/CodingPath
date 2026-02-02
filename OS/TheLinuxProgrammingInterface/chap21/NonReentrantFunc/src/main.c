#define _DEFAULT_SOURCE
#include <crypt.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "tlpi_hdr.h"

static char *g_inputString2; // For argv[2]
static int g_handleCount;

static void Handler(int sig)
{
    crypt(g_inputString2, "xx");
    ++g_handleCount;
}

int main(int argc, char *argv[])
{
    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s <str1> <str2>", argv[0]);

    g_inputString2 = argv[2];
    const char *inputString1 = argv[1];

    char *cryptString1 = strdup(crypt(inputString1, "xx"));
    if (!cryptString1)
        errExit("crypt str1");

    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = Handler;
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        errExit("sigaction");

    for (int callCnt = 1, mismatchCnt = 0;; ++callCnt)
    {
        if (strcmp(crypt(inputString1, "xx"), cryptString1) != 0)
        {
            ++mismatchCnt;
            printf("\nMismatch on call %d, mismatch = %d, handled = %d\n", callCnt, mismatchCnt, g_handleCount);
        }
    }

    return 0;
}
