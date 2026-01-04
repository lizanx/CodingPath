#include <grp.h>
#include <pwd.h>
#include <stdbool.h>
#include "ugid_functions.h"
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    if (argc < 4 || (argc >= 2 && strcmp(argv[1], "--help") == 0))
        usageErr("%s <owner> <group> <file ...>\n"
                 "\towner or group can be '-' to be unchanged.\n",
                 argv[0]);

    uid_t uid;
    if (strcmp(argv[1], "-") == 0)
    {
        uid = (uid_t)(-1);
    }
    else
    {
        uid = userIdFromName(argv[1]);
        if (uid == (uid_t)(-1))
            errExit("Failed to find uid for %s", argv[1]);
    }

    gid_t gid;
    if (strcmp(argv[2], "-") == 0)
    {
        gid = (gid_t)(-1);
    }
    else
    {
        gid = groupIdFromName(argv[2]);
        if (gid == (gid_t)(-1))
            errExit("Failed to find gid for %s", argv[2]);
    }

    bool errFound = false;
    for (int i = argc - 1; i > 2; --i)
    {
        const char *file = argv[i];
        if (chown(file, uid, gid))
        {
            errMsg("Failed to chown for %s.\n", file);
            errFound = true;
        }
    }

    return errFound ? EXIT_FAILURE : EXIT_SUCCESS;
}
