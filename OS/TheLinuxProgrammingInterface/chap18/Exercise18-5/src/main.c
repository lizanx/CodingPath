#define _DEFAULT_SOURCE
#include <dirent.h>
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "tlpi_hdr.h"

static char g_pathBuffer[PATH_MAX];

static char *GetCwd(char *buf, size_t size)
{
    if (!buf || size == 0)
    {
        fprintf(stderr, "Invalid buffer.\n");
        return NULL;
    }

    char **pathStack = malloc(sizeof(char *) * PATH_MAX);
    if (!pathStack)
    {
        fprintf(stderr, "Failed to alloc for path stack.\n");
        return NULL;
    }
    int stackTop = 0;

    int fdCwd = -1;

    for (;;)
    {
        DIR *curDir = opendir(".");
        if (!curDir)
            errExit("Failed to open current dir.");
        struct stat curStat;
        if (fstat(dirfd(curDir), &curStat))
            errExit("Failed to stat current dir.");

        // Save fd for real current dir.
        bool closeCurDir = true;
        if (fdCwd < 0)
        {
            fdCwd = dirfd(curDir);
            closeCurDir = false;
        }

        DIR *parentDir = opendir("..");
        if (!parentDir)
            errExit("Failed to open parent dir.");
        struct dirent *entry = NULL;
        struct stat siblingStat;
        bool found = false;
        while ((entry = readdir(parentDir)) != NULL)
        {
            if (strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(g_pathBuffer, sizeof(g_pathBuffer) - 1, "../%s", entry->d_name);
            if (stat(g_pathBuffer, &siblingStat))
                errExit("Failed to stat %s in parent dir.", entry->d_name);
            if (siblingStat.st_ino == curStat.st_ino && siblingStat.st_dev == curStat.st_dev)
            {
                found = true;
                break;
            }
        }
        if (!found)
            errExit("Failed to find current dir in its parent dir.");

        bool isRootDir = strcmp(entry->d_name, ".") == 0;
        if (!isRootDir)
            pathStack[stackTop++] = strdup(entry->d_name);
        else
            pathStack[stackTop++] = strdup("");

        closedir(parentDir);
        if (closeCurDir)
            closedir(curDir);
        chdir("..");

        if (isRootDir)
            break;
    }
    fchdir(fdCwd);
    closedir(fdopendir(fdCwd));

    memset(g_pathBuffer, 0, sizeof(g_pathBuffer));
    for (int i = stackTop - 1; i >= 0; --i)
    {
        strcat(g_pathBuffer, pathStack[i]);
        strcat(g_pathBuffer, "/");
        free(pathStack[i]);
        pathStack[i] = NULL;
    }
    free(pathStack);
    g_pathBuffer[strlen(g_pathBuffer) - 1] = '\0'; // Remove trailing '/'
    if (strlen(g_pathBuffer) < size)
    {
        strcpy(buf, g_pathBuffer);
        return buf;
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    char buf[PATH_MAX];
    if (!GetCwd(buf, sizeof(buf)))
        fprintf(stderr, "!!! Failed to get cwd !!!\n");
    else
        printf("Cwd: %s\n", buf);

    return 0;
}
