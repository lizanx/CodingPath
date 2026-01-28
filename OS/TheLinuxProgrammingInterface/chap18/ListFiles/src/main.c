#define _DEFAULT_SOURCE
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include "tlpi_hdr.h"

static int ListDir(const char *dirPath)
{
    bool isCwd = strcmp(dirPath, ".") == 0;

    DIR *dir = opendir(dirPath);
    if (!dir)
    {
        fprintf(stderr, "Failed to open %s\n", dirPath);
        return -1;
    }

    struct dirent *entry = NULL;
    for (;;)
    {
        errno = 0;
        entry = readdir(dir);
        if (!entry)
            break; // Error or end of list
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        if (!isCwd)
            printf("%s/", dirPath);
        printf("%s\n", entry->d_name);
    }

    if (errno)
    {
        fprintf(stderr, "Failure during reading dir %s, errno = %d\n", dirPath, errno);
        if (closedir(dir))
        {
            fprintf(stderr, "Failed to close %s\n", dirPath);
            return -2;
        }
        return -3;
    }

    if (closedir(dir))
    {
        fprintf(stderr, "Failed to close %s\n", dirPath);
        return -4;
    }

    return 0;
}

// Use "readdir_r" instead of "readdir"
static int ListDir2(const char *dirPath)
{
    bool isCwd = strcmp(dirPath, ".") == 0;

    DIR *dir = opendir(dirPath);
    if (!dir)
    {
        fprintf(stderr, "Failed to open %s\n", dirPath);
        return -1;
    }

    size_t dirEntrySize = offsetof(struct dirent, d_name) + NAME_MAX + 1;
    struct dirent *entry = malloc(dirEntrySize);
    if (!entry)
    {
        fprintf(stderr, "Failed to alloc for direntry\n");
        return -2;
    }
    struct dirent *result = NULL;
    for (;;)
    {
        int rc = readdir_r(dir, entry, &result);
        if (rc)
        {
            fprintf(stderr, "Failure during readding dir %s, rc = %d\n", dirPath, rc);
            if (closedir(dir))
            {
                fprintf(stderr, "Failed to close %s\n", dirPath);
                return -3;
            }
            return -4;
        }
        if (!result)
            break; // End of file list
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        if (!isCwd)
            printf("%s/", dirPath);
        printf("%s\n", entry->d_name);
    }

    if (closedir(dir))
    {
        fprintf(stderr, "Failed to close %s\n", dirPath);
        return -5;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        usageErr("%s [dir1 dir2 dir3 ...]\n", argv[0]);

    int rc = 0;
    if (argc == 1)
    {
        if ((rc = ListDir(".")) != 0)
        {
            fprintf(stderr, "!!! Failed to list current dir !!! rc = %d\n", rc);
            exit(rc);
        }
    }
    else
    {
        for (int i = 1; i < argc; ++i)
            if ((rc = ListDir2(argv[i])) != 0)
            {
                fprintf(stderr, "!!! Failed to list dir %s !!! rc = %d\n", argv[i], rc);
                exit(rc);
            }
    }

    return 0;
}
