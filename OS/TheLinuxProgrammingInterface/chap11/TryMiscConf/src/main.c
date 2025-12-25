#include <stdio.h>
#include <unistd.h>
#include "tlpi_hdr.h"

static void PrintSysConf(const char *msg, int name)
{
    errno = 0;
    long limit = sysconf(name);
    if (limit < 0)
    {
        if (errno)
            errExit("Failed to call sysconf.");
        printf("Indeterminate result.\n");
        return;
    }

    printf("%s: %ld\n", msg, limit);
}

static void PrintPathConf(const char *msg, int name)
{
    errno = 0;
    long limit = pathconf("/", name);
    if (limit < 0)
    {
        if (errno)
            errExit("Failed to call pathconf.");
        printf("Indeterminate result.\n");
        return;
    }

    printf("%s: %ld\n", msg, limit);
}

int main(int argc, char *argv[])
{
    printf("======================== SysConf ========================\n");
    PrintSysConf("Function args buf max", _SC_ARG_MAX);
    PrintSysConf("Login name length max", _SC_LOGIN_NAME_MAX);
    PrintSysConf("File open count max", _SC_OPEN_MAX);
    PrintSysConf("Supplementary group count max", _SC_NGROUPS_MAX);
    PrintSysConf("Page size", _SC_PAGE_SIZE);
    PrintSysConf("Real-time signal max", _SC_RTSIG_MAX);

    printf("======================== PathConf ========================\n");
    PrintPathConf("File name max length", _PC_NAME_MAX);
    PrintPathConf("Path max length", _PC_PATH_MAX);
    PrintPathConf("Pipe buffer max size", _PC_PIPE_BUF);

    printf("======================== System Implementation ========================\n");
#ifdef _POSIX_ASYNCHRONOUS_IO
    PrintSysConf("POSIX async io support", _SC_ASYNCHRONOUS_IO);
#endif
#ifdef _POSIX_CHOWN_RESTRICTED
    PrintPathConf("POSIX chown restriction support", _PC_CHOWN_RESTRICTED);
#endif
#ifdef _POSIX_JOB_CONTROL
    PrintSysConf("POSIX job control support", _SC_JOB_CONTROL);
#endif
#ifdef _POSIX_MESSAGE_PASSING
    PrintSysConf("POSIX msg queue support", _SC_MESSAGE_PASSING);
#endif
#ifdef _POSIX_PRIORITY_SCHEDULING
    PrintSysConf("POSIX priority scheduling support", _SC_PRIORITY_SCHEDULING);
#endif
#ifdef _POSIX_REALTIME_SIGNALS
    PrintSysConf("POSIX real-time signals support", _SC_REALTIME_SIGNALS);
#endif
#ifdef _POSIX_SAVED_IDS
    printf("POSIX saved set-u/g-id supported\n");
#endif
#ifdef _POSIX_SEMAPHORES
    PrintSysConf("POSIX semaphores support", _SC_SEMAPHORES);
#endif
#ifdef _POSIX_SHARED_MEMORY_OBJECTS
    PrintSysConf("POSIX shared mem objs support", _SC_SHARED_MEMORY_OBJECTS);
#endif
#ifdef _POSIX_THREADS
    PrintSysConf("POSIX threads support", _SC_THREADS);
#endif
#ifdef _XOPEN_UNIX
    PrintSysConf("POSIX XSI extensions support", _SC_XOPEN_UNIX);
#endif

    return 0;
}
