#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define SHARED_MEM_SIZE 1024
#define SHARED_MEM_NAME "/shm-demo"
#define SEMAPHORE_NAME "/sem-demo"

static sem_t *sem;

static void *get_shared_memory()
{
    int is_create = 0;
    int shm_fd = shm_open(SHARED_MEM_NAME, O_CREAT | O_EXCL | O_RDWR, 0666);
    if (shm_fd > 0)
    {
        is_create = 1;
        printf("Creating shared memory and setting size = %d\n", SHARED_MEM_SIZE);
        if (ftruncate(shm_fd, SHARED_MEM_SIZE) < 0)
        {
            perror("Failed to resize shared memory.");
            exit(1);
        }
        sem = sem_open(SEMAPHORE_NAME, O_RDWR | O_CREAT, 0666, 1);
        if (sem == SEM_FAILED)
        {
            perror("Failed to create semaphore.");
            exit(2);
        }
    }
    else if (shm_fd == -1 && errno == EEXIST)
    {
        shm_fd = shm_open(SHARED_MEM_NAME, O_RDWR, 0);
        sem = sem_open(SEMAPHORE_NAME, O_RDWR);
        if (sem == SEM_FAILED)
        {
            perror("Failed to open semaphore.");
            exit(3);
        }
    }

    if (shm_fd < 0)
    {
        perror("Failed to shm_open " SHARED_MEM_NAME);
        exit(4);
    }

    void *shm_ptr = mmap(NULL, SHARED_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (!shm_ptr)
    {
        perror("Failed to mmap.");
        exit(5);
    }
    if (is_create)
        memset(shm_ptr, 0, SHARED_MEM_SIZE);

    return shm_ptr;
}

int main(int argc, char *argv[])
{
    pid_t pid = getpid();
    printf("%s PID=%d\n", argv[0], pid);

    int count = 0;
    char *shm_ptr = get_shared_memory();
    while (1)
    {
        printf("Press ENTER to see the current contents of shm\n");
        getchar();
        sem_wait(sem);
        printf("%s\n", shm_ptr);
        sprintf(shm_ptr, "Hello from process %d, round %d\n", pid, ++count);
        sem_post(sem);
    }

    return EXIT_SUCCESS;
}
