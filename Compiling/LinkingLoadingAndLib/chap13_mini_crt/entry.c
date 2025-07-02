#include "minicrt.h"

#ifdef WIN32
#include <Windows.h>
#endif

extern int main(int argc, char *argv[]);

void exit(int);

static void crt_fatal_error(const char *msg)
{
    // printf("Fatal error: %s\n", msg);
    exit(1);
}

void mini_crt_entry()
{
#ifdef WIN32
    int flag = 0;
    int argc = 0;
    char *argv[16]; // 16 command line arguments at most
    char *cl = GetCommandLineA();
    // Parse command line arguments
    argv[0] = cl;
    ++argc;
    while (*cl)
    {
        if (*cl == '\"')
        {
            if (flag == 0)
                flag = 1;
            else
                flag = 0;
        }
        else if (*cl == ' ' && flag == 0)
        {
            if (*(cl + 1))
            {
                argv[argc] = cl + 1;
                ++argc;
            }
            *cl = '\0';
        }
        ++cl;
    }
#else
    int argc;
    char **argv;
    char *ebp_reg = NULL;
    // ebp_reg = %ebp
    asm("movl %%ebp,%0 \n" : "=r"(ebp_reg));
    argc = *(int *)(ebp_reg + 4);
    argv = (char **)(ebp_reg + 8);
#endif /* WIN32 */

    if (!mini_crt_heap_init())
        crt_fatal_error("Heap initialization failed!");

    if (!mini_crt_io_init())
        crt_fatal_error("IO initialization failed!");

    do_global_ctors();

    int ret = main(argc, argv);

    exit(ret);
}

void exit(int exit_code)
{
    mini_crt_call_exit_routine();

#ifdef WIN32
    ExitProcess(exit_code);
#else
    asm("movl %0,%%ebx \n\t"
        "movl $1,%%eax \n\t"
        "int $0x80 \n\t"
        "hlt \n\t" ::"m"(exit_code));
#endif /* WIN32 */
}
