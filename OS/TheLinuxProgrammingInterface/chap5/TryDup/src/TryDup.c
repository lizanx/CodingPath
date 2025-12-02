#define _GNU_SOURCE
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "tlpi_hdr.h"

const char g_normalMsg[] = "Hello, world!";
const char g_errMsg[] = "Error!";

static void PrintUsageInfo()
{
    usageErr("TryDup [open | dup | dup2 | dup3 | fcntl]");
}

static void RedirectWithOpen()
{
    if (close(STDOUT_FILENO) < 0)
        errExit("Failed to close stdout.");
    int fd_stdout = open("tmp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd_stdout < 0)
        errExit("Failed to open tmp.txt.");
    assert(fd_stdout == STDOUT_FILENO);

    if (close(STDERR_FILENO) < 0)
        errExit("Failed to close stderr.");
    int fd_stderr = open("tmp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd_stderr < 0)
        errExit("Failed to open tmp.txt.");
    assert(fd_stderr == STDERR_FILENO);

    write(STDOUT_FILENO, g_normalMsg, sizeof(g_normalMsg));
    write(STDERR_FILENO, g_errMsg, sizeof(g_errMsg));

    if (close(fd_stdout) < 0)
        errExit("Failed to close %d.", fd_stdout);
    if (close(fd_stderr) < 0)
        errExit("Failed to close %d.", fd_stderr);
}

static void RedirectWithDup()
{
    if (close(STDOUT_FILENO) < 0)
        errExit("Failed to close stdout.");
    int fd_stdout = open("tmp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd_stdout < 0)
        errExit("Failed to open tmp.txt.");
    assert(fd_stdout == STDOUT_FILENO);

    if (close(STDERR_FILENO) < 0)
        errExit("Failed to close stderr.");
    int fd_stderr = dup(fd_stdout);
    if (fd_stderr < 0)
        errExit("Failed to dup fd_stdout.");
    assert(fd_stderr == STDERR_FILENO);

    write(STDOUT_FILENO, g_normalMsg, sizeof(g_normalMsg));
    write(STDERR_FILENO, g_errMsg, sizeof(g_errMsg));

    if (close(fd_stdout) < 0)
        errExit("Failed to close %d.", fd_stdout);
    if (close(fd_stderr) < 0)
        errExit("Failed to close %d.", fd_stderr);
}

static void RedirectWithDup2()
{
    if (close(STDOUT_FILENO) < 0)
        errExit("Failed to close stdout.");
    int fd_stdout = open("tmp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd_stdout < 0)
        errExit("Failed to open tmp.txt.");
    assert(fd_stdout == STDOUT_FILENO);

    int fd_stderr = dup2(fd_stdout, STDERR_FILENO);
    if (fd_stderr < 0)
        errExit("Failed to dup fd_stdout.");
    assert(fd_stderr == STDERR_FILENO);

    write(STDOUT_FILENO, g_normalMsg, sizeof(g_normalMsg));
    write(STDERR_FILENO, g_errMsg, sizeof(g_errMsg));

    if (close(fd_stdout) < 0)
        errExit("Failed to close %d.", fd_stdout);
    if (close(fd_stderr) < 0)
        errExit("Failed to close %d.", fd_stderr);
}

static void RedirectWithDup3()
{
    if (close(STDOUT_FILENO) < 0)
        errExit("Failed to close stdout.");
    int fd_stdout = open("tmp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd_stdout < 0)
        errExit("Failed to open tmp.txt.");
    assert(fd_stdout == STDOUT_FILENO);

    int fd_stderr = dup3(fd_stdout, STDERR_FILENO, 0);
    if (fd_stderr < 0)
        errExit("Failed to dup fd_stdout.");
    assert(fd_stderr == STDERR_FILENO);

    write(STDOUT_FILENO, g_normalMsg, sizeof(g_normalMsg));
    write(STDERR_FILENO, g_errMsg, sizeof(g_errMsg));

    if (close(fd_stdout) < 0)
        errExit("Failed to close %d.", fd_stdout);
    if (close(fd_stderr) < 0)
        errExit("Failed to close %d.", fd_stderr);
}

static void RedirectWithFcntl()
{
    if (close(STDOUT_FILENO) < 0)
        errExit("Failed to close stdout.");
    int fd_stdout = open("tmp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd_stdout < 0)
        errExit("Failed to open tmp.txt.");
    assert(fd_stdout == STDOUT_FILENO);

    if (close(STDERR_FILENO) < 0)
        errExit("Failed to close stderr.");
    int fd_stderr = fcntl(fd_stdout, F_DUPFD, STDERR_FILENO);
    if (fd_stderr < 0)
        errExit("Failed to dup fd_stdout.");
    assert(fd_stderr == STDERR_FILENO);

    write(STDOUT_FILENO, g_normalMsg, sizeof(g_normalMsg));
    write(STDERR_FILENO, g_errMsg, sizeof(g_errMsg));

    if (close(fd_stdout) < 0)
        errExit("Failed to close %d.", fd_stdout);
    if (close(fd_stderr) < 0)
        errExit("Failed to close %d.", fd_stderr);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        PrintUsageInfo();
        exit(0);
    }

    const char *pattern = argv[argc - 1];
    if (strcmp(pattern, "open") == 0)
        RedirectWithOpen();
    else if (strcmp(pattern, "dup") == 0)
        RedirectWithDup();
    else if (strcmp(pattern, "dup2") == 0)
        RedirectWithDup2();
    else if (strcmp(pattern, "dup3") == 0)
        RedirectWithDup3();
    else if (strcmp(pattern, "fcntl") == 0)
        RedirectWithFcntl();
    else
        errExit("Unknown pattern %s", pattern);

    return 0;
}
