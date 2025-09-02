#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char shared_data[32] = {'\0'};
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;

static void *producer(void *)
{
    static int cnt = 0;
    while (1)
    {
        sleep(1);
        pthread_mutex_lock(&mutex);
        snprintf(shared_data, sizeof(shared_data), "Produced data: %d", ++cnt);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond_var);
    }
    return NULL;
}

static void *consumer(void *)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        while (strlen(shared_data) == 0)
            pthread_cond_wait(&cond_var, &mutex);
        printf("[Shared data] %s\n", shared_data);
        memset(shared_data, 0, sizeof(shared_data));
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}
