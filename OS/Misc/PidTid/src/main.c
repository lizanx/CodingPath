#define _GNU_SOURCE // Must define this before including any headers to use "gettid", otherwise do syscall directly.
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

static void show_pid_tid()
{
    printf("PID: %d, TID: %d %d\n", getpid(), gettid(), (pid_t)syscall(SYS_gettid));
}

static void *thread_fn(void *arg)
{
    int sleep_sec = (int)(uintptr_t)arg;
    printf("New thread, sleep for %d seconds.\n", sleep_sec);
    sleep(sleep_sec);
    show_pid_tid();
    return NULL;
}

int main(int argc, char *argv[])
{
    show_pid_tid();
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread_fn, (void *)2);
    pthread_create(&t2, NULL, thread_fn, (void *)3);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
