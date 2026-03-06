// From https://github.com/eliben/code-for-blog/blob/main/2011/simple_tracer.c
/* Code sample: using ptrace for simple tracing of a child process.
**
** Note: this was originally developed for a 32-bit x86 Linux system; some
** changes may be required to port to x86-64.
**
** Eli Bendersky (https://eli.thegreenplace.net)
** This code is in the public domain.
*/
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <signal.h>
#include <syscall.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <unistd.h>
#include <errno.h>

static void procmsg(const char *fmt, ...)
{
    va_list ap;
    fprintf(stdout, "[%d] ", getpid());
    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    va_end(ap);
}

static void run_target(const char *program)
{
    procmsg("target started. will run '%s'\n", program);

    // Allow tracing of this process.
    if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) < 0)
    {
        perror("ptrace");
        return;
    }

    execl(program, program, NULL);
}

static void run_debugger(pid_t child_pid)
{
    int wait_status;
    unsigned long icounter = 0;
    procmsg("debugger started\n");

    // Wait for child to stop on its first instruction
    wait(&wait_status);

    while (WIFSTOPPED(wait_status))
    {
        icounter++;
        struct user_regs_struct regs;
        ptrace(PTRACE_GETREGS, child_pid, 0, &regs);
        unsigned long instr = ptrace(PTRACE_PEEKTEXT, child_pid, regs.rip, 0);

        procmsg("icounter = %lu. RIP = %#018lX. instr = %#018lX\n", icounter, regs.rip, instr);

        // Make the child execute another instruction
        if (ptrace(PTRACE_SINGLESTEP, child_pid, NULL, 0) < 0)
        {
            perror("ptrace");
            return;
        }

        // Wait for child to stop on its next instruction
        wait(&wait_status);
    }

    procmsg("the child executed %u instrcutions\n", icounter);
}

int main(int argc, char *argv[])
{
    pid_t child_pid;

    if (argc < 2)
    {
        fprintf(stderr, "Expected a program name as argument\n");
        return -1;
    }

    child_pid = fork();
    if (child_pid == 0)
    {
        // child
        run_target(argv[1]);
    }
    else if (child_pid > 0)
    {
        // parent
        run_debugger(child_pid);
    }
    else
    {
        perror("fork");
        return -1;
    }

    return 0;
}
