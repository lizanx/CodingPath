#define _DEFAULT_SOURCE
#include <sys/inotify.h>
#include <limits.h>
#include "tlpi_hdr.h"

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

static void DisplayINotifyEvent(struct inotify_event *evt)
{
    if (!evt)
    {
        fprintf(stderr, "Failed to display event info.");
        return;
    }

    printf("\twd = %2d; ", evt->wd);
    if (evt->cookie > 0)
        printf("\tcookie = %34d", evt->cookie);
    printf("\tmask = ");
    if (evt->mask & IN_ACCESS)
        printf("IN_ACCESS ");
    if (evt->mask & IN_ATTRIB)
        printf("IN_ATTRIB ");
    if (evt->mask & IN_CLOSE_NOWRITE)
        printf("IN_CLOSE_NOWRITE ");
    if (evt->mask & IN_CLOSE_WRITE)
        printf("IN_CLOSE_WRITE ");
    if (evt->mask & IN_CREATE)
        printf("IN_CREATE ");
    if (evt->mask & IN_DELETE)
        printf("IN_DELETE ");
    if (evt->mask & IN_DELETE_SELF)
        printf("IN_DELETE_SELF ");
    if (evt->mask & IN_IGNORED)
        printf("IN_IGNORED ");
    if (evt->mask & IN_ISDIR)
        printf("IN_ISDIR ");
    if (evt->mask & IN_MODIFY)
        printf("IN_MODIFY ");
    if (evt->mask & IN_MOVE_SELF)
        printf("IN_MOVE_SELF ");
    if (evt->mask & IN_MOVED_FROM)
        printf("IN_MOVED_FROM ");
    if (evt->mask & IN_MOVED_TO)
        printf("IN_MOVED_TO ");
    if (evt->mask & IN_OPEN)
        printf("IN_OPEN ");
    if (evt->mask & IN_Q_OVERFLOW)
        printf("IN_Q_OVERFLOW ");
    if (evt->mask & IN_UNMOUNT)
        printf("IN_UNMOUNT ");
    printf("\n");

    if (evt->len > 0)
        printf("\tname = %s\n", evt->name);
}

int main(int argc, char *argv[])
{
    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s <path list..>\n", argv[0]);

    int fdINotify = inotify_init();
    if (fdINotify < 0)
        errExit("Failed to init inotify.");
    for (int i = 1; i < argc; ++i)
    {
        int wd = inotify_add_watch(fdINotify, argv[i], IN_ALL_EVENTS);
        if (wd < 0)
            errExit("Failed to add watch for %s\n", argv[i]);
        printf("Watching %s via wd %d\n", argv[i], wd);
    }

    char buf[BUF_LEN];
    for (;;) // Watch for events forever
    {
        ssize_t numRead = read(fdINotify, buf, sizeof(buf));
        if (numRead < 0)
            errExit("Failed to read inotify events.");
        for (char *p = buf; p < buf + numRead;)
        {
            struct inotify_event *evt = (struct inotify_event *)p;
            DisplayINotifyEvent(evt);
            p += sizeof(struct inotify_event) + evt->len;
        }
    }

    return 0;
}
