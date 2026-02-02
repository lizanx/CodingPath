#define _DEFAULT_SOURCE
#include <setjmp.h>
#include <signal.h>
#include <string.h>
#include "signal_functions.h"
#include "tlpi_hdr.h"

#define USE_SIGSETJUMP 1

static volatile sig_atomic_t g_canJump;
#ifdef USE_SIGSETJUMP
static sigjmp_buf g_jmpBuf;
#else
static jmp_buf g_jmpBuf;
#endif

static void SigHandler(int sig)
{
    printf("Received signal %d(%s), signal mask:\n", sig, strsignal(sig));
    printSigMask(stdout, NULL);

    if (!g_canJump)
    {
        printf("Jump buffer not set yet, doing a simple return.\n");
        return;
    }

#ifdef USE_SIGSETJUMP
    siglongjmp(g_jmpBuf, 1);
#else
    longjmp(g_jmpBuf, 1);
#endif
}

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);

    printSigMask(stdout, "Signal mask at start up:\n");

    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = SigHandler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1)
        errExit("sigaction");

#ifdef USE_SIGSETJUMP
    printf("=== Use sigsetjump ===\n");
    if (sigsetjmp(g_jmpBuf, 1) == 0)
        g_canJump = 1;
    else
        printSigMask(stdout, "After jump from handler, signal mask is:\n");
#else
    printf("=== Use setjump ===\n");
    if (setjmp(g_jmpBuf) == 0)
        g_canJump = 1;
    else
        printSigMask(stdout, "After jump from handler, signal mask is:\n");
#endif

    for (;;)
        pause();

    return 0;
}
