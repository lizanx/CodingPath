#define _DEFAULT_SOURCE
#include <grp.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "tlpi_hdr.h"

#define SUPPLEMENTARY_GROUP_MAX (NGROUPS_MAX + 1)

static bool isUserInGroup(const char *user, const struct group *grp)
{
    if (!user || !grp || !grp->gr_mem)
        return false;
    for (const char **member = grp->gr_mem; *member; ++member)
    {
        if (strcmp(user, *member) == 0)
            return true;
    }
    return false;
}

static int customInitGroups(const char *user, gid_t group)
{
    if (!user)
        return -1;

    gid_t groups[SUPPLEMENTARY_GROUP_MAX];
    int cnt = 0;
    groups[cnt++] = group;
    setgrent();
    struct group *grp = NULL;
    while ((grp = getgrent()) != NULL && cnt < SUPPLEMENTARY_GROUP_MAX)
    {
        if (grp->gr_gid == group)
            continue;
        if (isUserInGroup(user, grp))
            groups[cnt++] = grp->gr_gid;
    }
    endgrent();

    if (setgroups(cnt, groups))
        return -2;

    return 0;
}

int main(int argc, char *argv[])
{

    return 0;
}
