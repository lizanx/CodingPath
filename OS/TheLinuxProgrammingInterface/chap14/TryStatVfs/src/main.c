#include <sys/statvfs.h>
#include <stdio.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
        usageErr("program <path>");

    const char *file = argv[1];

    struct statvfs svfs;
    if (statvfs(file, &svfs))
        errExit("Failed to get get vfs stat.");

    printf("Block size: %lu\n", svfs.f_bsize);
    printf("Fundamental block size: %lu\n", svfs.f_frsize);
    printf("Total blocks cnt: %lu\n", svfs.f_blocks);
    printf("Free blocks cnt: %lu\n", svfs.f_bfree);
    printf("Available blocks cnt(for non-root user): %lu. %lu blocks reserved for root-user.\n",
           svfs.f_bavail, svfs.f_bfree - svfs.f_bavail);
    printf("Total i-nodes cnt: %lu\n", svfs.f_files);
    printf("Free i-nodes cnt: %lu\n", svfs.f_ffree);
    printf("Available i-nodes cnt: %lu. %lu i-nodes reserved for root-user.\n",
           svfs.f_favail, svfs.f_ffree - svfs.f_favail);
    printf("Filesystem ID: %lu\n", svfs.f_fsid);
    printf("Mount flags: %#lX\n", svfs.f_flag);
    printf("Max length of file name: %lu\n", svfs.f_namemax);

    return 0;
}
