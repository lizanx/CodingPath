// #define _DEFAULT_SOURCE
#define _GNU_SOURCE
#include <limits.h>
#include <stdio.h>
#include <sys/fsuid.h>
#include <unistd.h>
#include "tlpi_hdr.h"

#define SUPPLEMENTARY_GROUP_MAX (NGROUPS_MAX + 1)

int main(int argc, char *argv[])
{
    uid_t ruid, euid, suid;
    gid_t rgid, egid, sgid;

    ruid = getuid();
    printf("getuid: ruid = %u\n", ruid);
    euid = geteuid();
    printf("geteuid: euid = %u\n", euid);
    if (getresuid(&ruid, &euid, &suid))
        errExit("Failed to call getresuid.");
    printf("getresuid: ruid = %u, euid = %u, suid = %u\n", ruid, euid, suid);

    rgid = getgid();
    printf("getgid: rgid = %u\n", rgid);
    egid = getegid();
    printf("getegid: egid = %u\n", egid);
    if (getresgid(&rgid, &egid, &sgid))
        errExit("Failed to call getresgid.");
    printf("getresgid: rgid = %u, egid = %u, sgid = %u\n", rgid, egid, sgid);

    if (euid != 0) // not root
    {
        uid_t fsuid = setfsuid(0);
        gid_t fsgid = setfsgid(0);
        printf("fsuid = %u, fsgid = %u\n", fsuid, fsgid);
    }

    gid_t supplementaryGroups[SUPPLEMENTARY_GROUP_MAX];
    int supplementaryGroupCnt = getgroups(SUPPLEMENTARY_GROUP_MAX, supplementaryGroups);
    if (supplementaryGroupCnt)
    {
        for (int i = 0; i < supplementaryGroupCnt; ++i)
            printf("SupplementaryGroup[%d]: gid = %u\n", i, supplementaryGroups[i]);
    }
    else
    {
        printf("No supplementary groups found.\n");
    }

    if (euid != 0)
    {
        printf("Effective uid is not root, return.\n");
        return 0;
    }

    if (ruid == 0)
    {
        printf("Real uid is root, return.\n");
        return 0;
    }

    // euid == 0, ruid != 0
    // Set euid to ruid, and then set it back.
    printf("Change euid(%u) to ruid(%u)..\n", euid, ruid);
    if (seteuid(ruid))
        errExit("Failed to set euid to ruid %u", ruid);
    if (getresuid(&ruid, &euid, &suid))
        errExit("Failed to get r/e/s uid.");
    printf("Change done: ruid = %u , euid = %u, suid = %u\n", ruid, euid, suid);
    printf("Change euid back..\n");
    if (seteuid(suid))
        errExit("Failed to set euid to suid %u", suid);
    if (getresuid(&ruid, &euid, &suid))
        errExit("Failed to get r/e/s uid.");
    printf("Change done: ruid = %u , euid = %u, suid = %u\n", ruid, euid, suid);

    return 0;
}
