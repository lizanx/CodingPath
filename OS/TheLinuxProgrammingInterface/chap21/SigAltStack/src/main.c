#define _DEFAULT_SOURCE
#include <signal.h>
#include <string.h>
#include "tlpi_hdr.h"

static void SegvHandler(int sig)
{
    int x = 0;

    printf("Caught signal %d (%s)\n", sig, strsignal(sig));
    printf("Top of handler stack near %p\n", &x);

    _exit(EXIT_FAILURE);
}

static void OverflowStackFunc(int callNum)
{
    char array[1024];

    printf("Call %d - top of stack near %p\n", callNum, array);
    OverflowStackFunc(callNum + 1);
}

int main(int argc, char *argv[])
{
    int i = 0;

    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Top of standard stack is near %p\n", &i);

    stack_t altStack = {
        .ss_flags = 0,
        .ss_size = SIGSTKSZ,
        .ss_sp = malloc(SIGSTKSZ)};
    if (!altStack.ss_sp)
        errExit("Failed to allocate memory for alternative signal stack.");
    if (sigaltstack(&altStack, NULL) == -1)
        errExit("Failed to set alternate signal stack.");
    printf("Alternate signal stack is at %p ~ %p\n", altStack.ss_sp, altStack.ss_sp + altStack.ss_size - 1);

    struct sigaction sa = {
        .sa_flags = SA_ONSTACK,
        .sa_handler = SegvHandler};
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGSEGV, &sa, NULL) == -1)
        errExit("Failed to set SEGV handler.");

    OverflowStackFunc(1);

    return 0;
}
