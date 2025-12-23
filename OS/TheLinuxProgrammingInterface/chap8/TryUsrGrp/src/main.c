// #define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#include <grp.h>
#include <pwd.h>
#include <shadow.h>
#include <stdio.h>
#include <unistd.h>
#include "tlpi_hdr.h"

#define USER_NAME "lizan"
#define USER_ID 1000
#define GROUP_NAME "lizan"
#define GROUP_ID 1000

static void PrintPwdInfo(const struct passwd *pwd)
{
    printf("User name: %s\n", pwd->pw_name);
    printf("Encrypted password: %s\n", pwd->pw_passwd);
    printf("User ID: %u\n", pwd->pw_uid);
    printf("Group ID: %u\n", pwd->pw_gid);
    printf("Comment(user info): %s\n", pwd->pw_gecos);
    printf("User home dir: %s\n", pwd->pw_dir);
    printf("User shell: %s\n", pwd->pw_shell);
}

static void PrintGroupInfo(const struct group *grp)
{
    printf("Group name: %s\n", grp->gr_name);
    printf("Encrypted group pwd: %s\n", grp->gr_passwd);
    printf("Group ID: %u\n", grp->gr_gid);
    for (char **groupMember = grp->gr_mem; *groupMember; ++groupMember)
    {
        printf("Group member: %s\n", *groupMember);
    }
}

int main(int argc, char *argv[])
{
    // User functions
    const struct passwd *pwd = getpwnam(USER_NAME);
    if (!pwd)
        errExit("Failed to get pwd by name.");
    printf(">> Info for user with name '%s':\n", USER_NAME);
    PrintPwdInfo(pwd);

    pwd = getpwuid(USER_ID);
    if (!pwd)
        errExit("Failed to get pwd by uid.");
    printf("\n>> Info for user with uid '%u':\n", USER_ID);
    PrintPwdInfo(pwd);

    printf("\n>> Info for user with re-entrant functions\n");
    // ---> below call to get user name may fail in WSL due to missing connected controlling terminal, thus acquire user id instead. <---
    // const char *userName = getlogin();
    // if (!userName)
    //     errExit("Failed to get user name.");
    // char userNameBuf[_SC_LOGIN_NAME_MAX];
    // if (getlogin_r(userNameBuf, _SC_LOGIN_NAME_MAX) != 0)
    //     errExit("Failed to get user name by _r.");
    uid_t userId = getuid();
    printf(">> Info for user with uid '%u':\n", userId);
    struct passwd userPwd;
    struct passwd *userPwdResult;
    long infoBufSize = sysconf(_SC_GETPW_R_SIZE_MAX);
    if (infoBufSize < 0)
        errExit("Failed to get pwd buf size max.");
    char *buf = malloc(infoBufSize);
    if (!buf)
        errExit("Failed to malloc buf.");
    if (getpwuid_r(userId, &userPwd, buf, infoBufSize, &userPwdResult) != 0)
        errExit("Failed to get pwd by _r.");
    // if (getpwnam_r(userName, &userPwd, buf, infoBufSize, &userPwdResult) != 0)
    //     errExit("Failed to get pwd by _r.");
    if (userPwdResult == NULL)
        errExit("Failed to found user with uid '%u'", userId);
    PrintPwdInfo(&userPwd);
    free(buf);

    // Group functions
    const struct group *grp = getgrnam(GROUP_NAME); // similar func with "_s" suffix is like the one with user functions, demo is skipped here.
    if (!grp)
        errExit("Failed to get group by name.");
    printf("\n>> Info for group with name '%s':\n", GROUP_NAME);
    PrintGroupInfo(grp);

    gid_t groupId = getgid();
    grp = getgrgid(groupId);
    if (!grp)
        errExit("Failed to get group by id.");
    printf("\n>> Info for group with ID '%u':\n", groupId);
    PrintGroupInfo(grp);

    // Loop through /etc/passwd items.
    printf("\n>> Loop through all pwd entries.\n");
    while ((pwd = getpwent()) != NULL)
    {
        printf("--> pwd entry <--\n");
        PrintPwdInfo(pwd);
    }
    endpwent();

    // Shadow passwd. --> Need root privilege to read shadow pwd file.
    printf("\n>> Shadow passwd.\n");
    struct spwd *shadowPwd = NULL;
    while ((shadowPwd = getspent()) != NULL)
    {
        printf("--> spwd entry <--\n");
        printf("User name: %s\n", shadowPwd->sp_namp);
        printf("Encrypted pwd: %s\n", shadowPwd->sp_pwdp);
    }
    endspent();

    return 0;
}
