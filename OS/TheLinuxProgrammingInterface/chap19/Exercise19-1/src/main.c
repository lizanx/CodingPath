#define _XOPEN_SOURCE 600
#include <ftw.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#include <unistd.h>
#include "tlpi_hdr.h"

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))
#define WATCH_DESCRIPTOR_LIST_DEFAULT_LEN (32)
#define EVENT_MASK (IN_CREATE | IN_DELETE | IN_MOVE)

typedef struct WatchDescriptorList
{
    int *wds;
    char **paths;
    int size;
    int capacity;
} WatchDescriptorList;

static char g_pathBuf[PATH_MAX];
static char g_inotifyEventBuf[BUF_LEN];
static WatchDescriptorList g_wdList;
static int g_fdINotify;

static int FindWatchItemByWd(WatchDescriptorList *wdList, int wd)
{
    int i = 0;
    for (; i < wdList->size; ++i)
    {
        if (wdList->wds[i] == wd)
            break;
    }
    return (i < wdList->size) ? i : -1;
}

static int FindWatchItemByPath(WatchDescriptorList *wdList, const char *path)
{
    int i = 0;
    for (; i < wdList->size; ++i)
    {
        if (strcmp(wdList->paths[i], path) == 0)
            break;
    }
    return (i < wdList->size) ? i : -1;
}

static void ExpandWatchDescriptorList(WatchDescriptorList *wdList)
{
    if (wdList->size < wdList->capacity)
        return;
    int newCapacity = (wdList->capacity > 0) ? wdList->capacity * 2 : WATCH_DESCRIPTOR_LIST_DEFAULT_LEN;
    int *newWds = malloc(sizeof(int) * newCapacity);
    if (!newWds)
        errExit("Failed to expand wds.");
    char **newPaths = malloc(sizeof(char *) * newCapacity);
    if (!newPaths)
        errExit("Failed to expand paths.");

    memcpy(newWds, wdList->wds, sizeof(int) * wdList->size);
    memcpy(newPaths, wdList->paths, sizeof(char *) * wdList->size);
    free(wdList->wds);
    free(wdList->paths);
    wdList->wds = newWds;
    wdList->paths = newPaths;
    wdList->capacity = newCapacity;
}

static int AddWatchDescriptorToList(WatchDescriptorList *wdList, int wd, const char *path)
{
    bool alreadyInList = false;
    for (int i = 0; i < wdList->size; ++i)
    {
        if (wdList->wds[i] == wd)
        {
            alreadyInList = true;
            break;
        }
    }
    if (alreadyInList)
    {
        fprintf(stderr, "Failed to add %s, wd %d already in list!", path, wd);
        return -1;
    }

    ExpandWatchDescriptorList(wdList);
    wdList->wds[wdList->size] = wd;
    wdList->paths[wdList->size] = strdup(path);
    if (!wdList->paths[wdList->size])
        errExit("Failed to dup path %s", path);
    ++wdList->size;

    return 0;
}

static int RemoveWatchDescriptorFromList(WatchDescriptorList *wdList, int wd)
{
    int i = 0;
    for (; i < wdList->size; ++i)
    {
        if (wdList->wds[i] == wd)
        {
            break;
        }
    }
    if (i == wdList->size)
    {
        // fprintf(stderr, "Failed to remove wd %d, not in list!", wd);
        return -1;
    }

    // Found
    memmove(wdList->wds + i, wdList->wds + i + 1, wdList->size - 1 - i);
    free(wdList->paths[i]);
    memmove(wdList->paths + i, wdList->paths + i + 1, wdList->size - 1 - i);
    --wdList->size;

    return 0;
}

static int WatchAllSubDirInTree(const char *pathname, const struct stat *sbuf, int type, struct FTW *ftwb)
{
    if (type == FTW_D && S_ISDIR(sbuf->st_mode))
    {
        int wd = inotify_add_watch(g_fdINotify, pathname, EVENT_MASK);
        if (wd < 0)
            errExit("Failed to watch %s", pathname);
        if (AddWatchDescriptorToList(&g_wdList, wd, pathname))
            errExit("Failed to add [%d | %s] to watch list.", wd, pathname);
        printf("%s added to watch list\n", pathname);
    }

    return 0;
}

static void HandleFileEvent(struct inotify_event *evt)
{
    // printf("Event triggered, mask = %#X, len = %d, name = %s\n", evt->mask, evt->len, evt->name);
    if (evt->mask & EVENT_MASK)
    {
        int index = FindWatchItemByWd(&g_wdList, evt->wd);
        if (index < 0)
            errExit("Failed to find the watched dir in list, wd = %d, name = %s", evt->wd, evt->name);
        const char *dirPath = g_wdList.paths[index];
        if (evt->len == 0)
            snprintf(g_pathBuf, sizeof(g_pathBuf), "%s", dirPath);
        else
            snprintf(g_pathBuf, sizeof(g_pathBuf), "%s/%s", dirPath, evt->name);
        struct stat st;
        memset(&st, 0, sizeof(st));

        if (evt->mask & IN_CREATE)
        {
            printf("-> %s created.\n", g_pathBuf);

            if (stat(g_pathBuf, &st))
                fprintf(stderr, "Failed to stat %s while handling event\n", g_pathBuf);
            if (S_ISDIR(st.st_mode))
            {
                int wd = inotify_add_watch(g_fdINotify, g_pathBuf, EVENT_MASK);
                if (wd < 0)
                    errExit("Failed to watch %s", g_pathBuf);
                if (AddWatchDescriptorToList(&g_wdList, wd, g_pathBuf))
                    fprintf(stderr, "Failed to add wd [%d | %s] to watch list.\n", wd, g_pathBuf);
            }
        }

        if (evt->mask & IN_DELETE)
        {
            printf("-> %s deleted.\n", g_pathBuf);
            int i = FindWatchItemByPath(&g_wdList, g_pathBuf);
            if (i >= 0)
            {
                printf("\tThe watched dir %s is deleted, remove it from watch list.\n", g_pathBuf);
                RemoveWatchDescriptorFromList(&g_wdList, g_wdList.wds[i]);
            }
        }

        if (evt->mask & IN_MOVED_FROM)
        {
            printf("-> move from %s.", g_pathBuf);
            int i = FindWatchItemByPath(&g_wdList, g_pathBuf);
            if (i >= 0)
            {
                printf("\tThe watched dir %s is moved, remove it from watch list.\n", g_pathBuf);
                RemoveWatchDescriptorFromList(&g_wdList, g_wdList.wds[i]);
            }
        }

        if (evt->mask & IN_MOVED_TO)
        {
            printf("-> move to %s.\n", g_pathBuf);
            if (stat(dirPath, &st))
                fprintf(stderr, "Failed to stat %s while handling event\n", dirPath);
            if (S_ISDIR(st.st_mode))
            {
                int wd = inotify_add_watch(g_fdINotify, g_pathBuf, EVENT_MASK);
                if (wd < 0)
                    errExit("Failed to watch %s", g_pathBuf);
                if (AddWatchDescriptorToList(&g_wdList, wd, g_pathBuf))
                    fprintf(stderr, "Failed to add wd [%d | %s] to watch list.\n", wd, g_pathBuf);
            }
        }

        fflush(stdout);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s <dir to monitor>\n", argv[0]);

    if (!realpath(argv[1], g_pathBuf))
        errExit("Failed to get real path for %s", argv[1]);
    char *rootDir = strdup(g_pathBuf);
    if (!rootDir)
        errExit("Failed to dup %s", g_pathBuf);

    struct stat st;
    if (stat(rootDir, &st))
        errExit("Failed to stat %s", rootDir);
    if (!S_ISDIR(st.st_mode))
        errExit("Not a directory!");

    g_fdINotify = inotify_init();
    if (g_fdINotify < 0)
        errExit("Failed to init inotify.");

    // int wd = inotify_add_watch(g_fdINotify, rootDir, EVENT_MASK);
    // if (wd < 0)
    //     errExit("Failed to watch rootdir.");
    // if (AddWatchDescriptorToList(&g_wdList, wd, rootDir))
    //     errExit("Failed to add root dir to wd list.");

    if (nftw(rootDir, WatchAllSubDirInTree, 10, 0) == -1)
        errExit("Failed to walk %s", rootDir);

    for (;;) // Watch for events forever
    {
        ssize_t numRead = read(g_fdINotify, g_inotifyEventBuf, sizeof(g_inotifyEventBuf));
        if (numRead < 0)
            errExit("Failed to read inotify events.");
        for (char *p = g_inotifyEventBuf; p < g_inotifyEventBuf + numRead;)
        {
            struct inotify_event *evt = (struct inotify_event *)p;
            HandleFileEvent(evt);
            p += sizeof(struct inotify_event) + evt->len;
        }
    }

    free(rootDir);
    return 0;
}
