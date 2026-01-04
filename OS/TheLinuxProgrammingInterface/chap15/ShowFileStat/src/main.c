#define _DEFAULT_SOURCE
#include <fcntl.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/time.h>
#include <time.h>
#include "file_perms.h"
#include "tlpi_hdr.h"

static void DisplayStatTimeInfo(const struct stat *st)
{
    if (!st)
        return;

    time_t tm = st->st_atim.tv_sec;
    printf("Last file access time: %s", ctime(&tm));
    tm = st->st_mtim.tv_sec;
    printf("Last file modification time: %s", ctime(&tm));
    tm = st->st_ctim.tv_sec;
    printf("Last file status change time: %s", ctime(&tm));
}

static void DisplayStatInfo(const struct stat *st)
{
    if (!st)
        return;

    printf("File type: ");
    switch (st->st_mode & S_IFMT)
    {
    case S_IFREG:
        printf("regular file\n");
        break;
    case S_IFDIR:
        printf("directory\n");
        break;
    case S_IFCHR:
        printf("char device\n");
        break;
    case S_IFBLK:
        printf("block device\n");
        break;
    case S_IFLNK:
        printf("symbolic link\n");
        break;
    case S_IFIFO:
        printf("FIFO or pipe\n");
        break;
    case S_IFSOCK:
        printf("socket\n");
        break;
    default:
        printf("Unkown file type\n");
        break;
    }

    printf("Device containing i-node: major = %ld, minor = %ld\n", (long)major(st->st_dev), (long)minor(st->st_dev));
    printf("i-node number: %ld\n", (long)st->st_ino);
    printf("Mode: %lo (%s)\n", (unsigned long)st->st_mode, filePermStr(st->st_mode, 0));
    if (st->st_mode & (S_ISUID | S_ISGID | S_ISVTX))
        printf("\tSpecial bits set: %s%s%s\n",
               (st->st_mode & S_ISUID) ? "set-UID " : "",
               (st->st_mode & S_ISGID) ? "set-GID " : "",
               (st->st_mode & S_ISVTX) ? "sticky" : "");
    printf("Number of hard links: %ld\n", (long)st->st_nlink);
    printf("Ownership: UID = %ld, GID = %ld\n", (long)st->st_uid, (long)st->st_gid);
    if (S_ISCHR(st->st_mode) || S_ISBLK(st->st_mode))
        printf("Device number(st_rdev): major = %ld, minor = %ld\n",
               (long)major(st->st_rdev), (long)minor(st->st_rdev));
    printf("File size: %lld bytes\n", (long long)st->st_size);
    printf("Optimal I/O block size: %ld bytes\n", (long)st->st_blksize);
    printf("Blocks allocated: %lld\n", (long long)st->st_blocks);
    DisplayStatTimeInfo(st);
}

static int GetStat(const char *path, bool statSymLink, struct stat *st)
{
    if (!path || !st)
        return -1;

    if (statSymLink)
    {
        return lstat(path, st);
    }
    else
    {
        return stat(path, st);
    }
}

int main(int argc, char *argv[])
{
    bool statSymLink = argc > 1 && strcmp(argv[1], "-l") == 0;
    int indexOfFilename = statSymLink ? 2 : 1;
    if (indexOfFilename >= argc || (argc > 1 && strcmp(argv[1], "--help") == 0))
        usageErr("%s [-l] <file>\n"
                 "\t-l = use lstat() instead of stat()\n",
                 argv[0]);
    const char *file = argv[indexOfFilename];

    struct stat st;
    if (GetStat(file, statSymLink, &st))
        errExit("Failed to get stat for %s", file);
    DisplayStatInfo(&st);

    printf("\n===== Sleep for 3s and show file time info again =====\n\n");

    sleep(3);
    if (GetStat(file, statSymLink, &st))
        errExit("Failed to get stat for %s", file);
    DisplayStatTimeInfo(&st);

    printf("\n===== Modify file access/modify time with 'utimes' and show file time info again =====\n\n");

    printf("Updating file a/m time to now..\n");
    struct timeval tv;
    if (gettimeofday(&tv, NULL))
        errExit("Failed to get time of day.");
    struct timeval tvs[2] = {
        [0] = {
            .tv_sec = tv.tv_sec,
            .tv_usec = tv.tv_usec,
        },
        [1] = {
            .tv_sec = tv.tv_sec,
            .tv_usec = tv.tv_usec,
        }};
    if (utimes(file, tvs))
        errExit("Failed to utimes.");
    if (GetStat(file, statSymLink, &st))
        errExit("Failed to get stat for %s", file);
    DisplayStatTimeInfo(&st);

    printf("\n===== Sleep for 3s and show file time info again =====\n\n");
    sleep(3);

    printf("\n===== Modify file access/modify time with 'utimesat' and show file time info again =====\n\n");
    struct timespec tss[2] = {
        [0] = {
            .tv_nsec = UTIME_NOW},
        [1] = {.tv_nsec = UTIME_OMIT}};
    if (utimensat(AT_FDCWD, file, tss, 0))
        errExit("Failed to utimesat.");
    if (GetStat(file, statSymLink, &st))
        errExit("Failed to get stat for %s", file);
    DisplayStatTimeInfo(&st);

    return 0;
}
