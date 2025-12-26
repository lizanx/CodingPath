#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <pwd.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "tlpi_hdr.h"

static uid_t GetUidByName(const char *name)
{
    if (!name)
    {
        fprintf(stderr, "Invalid name.\n");
        return -1;
    }

    struct passwd *pwd = getpwnam(name);
    if (!pwd)
    {
        fprintf(stderr, "Failed to get passwd for %s\n", name);
        return -2;
    }

    return pwd->pw_uid;
}

static void DisplayProcOwnedByUser(const char *procStatus, uid_t uid)
{
    if (!procStatus)
    {
        fprintf(stderr, "Invalid proc status path.\n");
        return;
    }

    FILE *fp = fopen(procStatus, "r");
    if (!fp)
    {
        fprintf(stderr, "Failed to open %s\n", procStatus);
        return;
    }
    char uidLine[128];
    char nameLine[128];
    bool uidLineFound = false;
    while (fgets(uidLine, 128, fp))
    {
        if (strncmp(uidLine, "Name:", 5) == 0)
        {
            strcpy(nameLine, uidLine);
        }
        if (strncmp(uidLine, "Uid:", 4) == 0)
        {
            uidLineFound = true;
            break;
        }
    }
    fclose(fp);
    if (!uidLineFound)
    {
        fprintf(stderr, "Failed to find uid line.\n");
        return;
    }
    // Parse line and find uid
    char *p = uidLine;
    while (!isdigit(*p))
        ++p;
    char procRuidbuf[32];
    memset(procRuidbuf, 0, sizeof(procRuidbuf));
    int cnt;
    for (cnt = 0; isdigit(*p) && cnt < sizeof(procRuidbuf); ++p, ++cnt)
        procRuidbuf[cnt] = *p;
    if (cnt >= sizeof(procRuidbuf))
    {
        fprintf(stderr, "Ruid too long, buf not large enough to accommodate it.\n");
        return;
    }
    uid_t procRuid = atol(procRuidbuf);
    if (procRuid == uid)
    {
        char *p = strstr(nameLine, "\n");
        if (p)
            *p = '\0';
        fprintf(stdout, "User(uid=%u) owns process %s\n", uid, nameLine);
    }
}

int main(int argc, char *argv[])
{
    uid_t uid;
    if (argc == 2)
    {
        uid = GetUidByName(argv[1]);
        if (uid == (uid_t)(-1) || uid == (uid_t)(-2))
            errExit("Failed to get uid by name %s", argv[1]);
    }
    else
    {
        uid = getuid();
    }

    DIR *procRootDir = opendir("/proc");
    if (!procRootDir)
        errExit("Failed to open proc root dir.");
    struct dirent *entry;
    while ((entry = readdir(procRootDir)) != NULL)
    {
        if (!isdigit(entry->d_name[0]))
            continue;
        size_t pathLen = strlen(entry->d_name) + strlen("/proc") + 2;
        char *buf = malloc(pathLen);
        if (!buf)
            errExit("Failed to allocate buffer for proc dir.");
        snprintf(buf, pathLen, "/proc/%s", entry->d_name);
        struct stat st;
        if (stat(buf, &st) < 0)
            errExit("Failed to get stat for dir %s", buf);
        if (!S_ISDIR(st.st_mode))
        {
            free(buf);
            continue;
        }
        buf = realloc(buf, strlen(buf) + strlen("/status") + 1);
        if (!buf)
            errExit("Failed to realloc buffer.");
        strcat(buf, "/status");
        DisplayProcOwnedByUser(buf, uid);
        free(buf);
    }
    closedir(procRootDir);

    return 0;
}
