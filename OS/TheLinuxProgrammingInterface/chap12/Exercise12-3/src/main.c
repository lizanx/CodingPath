#define _DEFAULT_SOURCE
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "tlpi_hdr.h"

static bool HasProcessOpenedFile(const char *pidDir, const char *file)
{
    if (!pidDir || !file)
        return false;

    char procFdDirPath[256];
    snprintf(procFdDirPath, sizeof(procFdDirPath), "%s/fd", pidDir);
    DIR *fdDir = opendir(procFdDirPath);
    if (!fdDir)
    {
        fprintf(stderr, "Failed to open fd dir %s\n", procFdDirPath);
        return false;
    }
    struct dirent *fdEntry;
    while ((fdEntry = readdir(fdDir)) != NULL)
    {
        if (strcmp(fdEntry->d_name, ".") == 0 || strcmp(fdEntry->d_name, "..") == 0)
            continue;

        char fdLinkPath[512];
        snprintf(fdLinkPath, sizeof(fdLinkPath), "%s/%s", procFdDirPath, fdEntry->d_name);

        struct stat st;
        if (lstat(fdLinkPath, &st) != 0 || !S_ISLNK(st.st_mode)) // Must use "lstat" here to check the link itself rather than its target.
            continue;

        char linkDestination[256];
        ssize_t n = readlink(fdLinkPath, linkDestination, sizeof(linkDestination));
        if (n < 0)
        {
            fprintf(stderr, "Failed to readlink at %s\n", fdLinkPath);
            continue;
        }
        linkDestination[n] = '\0';
        if (strcmp(linkDestination, file) == 0)
        {
            closedir(fdDir);
            return true;
        }
    }
    closedir(fdDir);
    return false;
}

static int
ReadProcName(const char *pidDir, char **procName)
{
    if (!procName)
        return -1;

    char path[256];
    snprintf(path, sizeof(path), "%s/status", pidDir);

    FILE *fp = fopen(path, "r");
    if (!fp)
        return -1;

    char line[512];
    char *name = NULL;

    while (fgets(line, sizeof(line), fp))
    {
        if (strncmp(line, "Name:", 5) == 0)
        {
            char *start = line + 5;
            while (isspace((unsigned char)*start))
                start++;
            char *end = strchr(start, '\n');
            if (end)
                *end = '\0';
            name = strdup(start);
            break;
        }
    }
    fclose(fp);

    if (!name)
    {
        return -1;
    }

    *procName = name;
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        usageErr("program <file path>");

    const char *targetFile = argv[1];
    printf("The target file to be searched: %s\n", targetFile);

    DIR *procDir = opendir("/proc");
    if (!procDir)
    {
        errExit("opendir /proc");
        return EXIT_FAILURE;
    }

    struct dirent *pidEntry;
    while ((pidEntry = readdir(procDir)) != NULL)
    {
        if (!isdigit(pidEntry->d_name[0]))
            continue;

        char pid_dir[512];
        snprintf(pid_dir, sizeof(pid_dir), "/proc/%s", pidEntry->d_name);

        struct stat st;
        if (stat(pid_dir, &st) != 0 || !S_ISDIR(st.st_mode))
            continue;

        if (HasProcessOpenedFile(pid_dir, targetFile))
        {
            pid_t pid = atoi(pidEntry->d_name);
            char *procName = NULL;
            if (ReadProcName(pid_dir, &procName) < 0)
                errExit("Failed to get name of process %d", pid);
            printf("%s[%d]\n", procName, pid);
            free(procName);
        }
    }
    closedir(procDir);

    return EXIT_SUCCESS;
}
