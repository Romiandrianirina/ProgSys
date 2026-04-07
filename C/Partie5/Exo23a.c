#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define NB_ITER 10

sem_t sem_T1, sem_T2;

void *thread_T1(void *arg)
{
    for (int i = 1; i <= NB_ITER; i++)
    {
        printf("T1 : début itération %d\n", i);
        sleep(2); // traitement fixe 2 secondes
        printf("T1 : fin itération %d\n", i);
        sem_post(&sem_T1); // signale à T2 que T1 a fini
        sem_wait(&sem_T2); // attend que T2 ait fini
    }
    return NULL;
}

void *thread_T2(void *arg)
{
    for (int i = 1; i <= NB_ITER; i++)
    {
        printf("T2 : début itération %d\n", i);
        int duree = rand() % 6 + 4; // 4 à 9 secondes
        sleep(duree);
        printf("T2 : fin itération %d\n", i);
        sem_post(&sem_T2); // signale à T1 que T2 a fini
        sem_wait(&sem_T1); // attend que T1 ait fini
    }
    return NULL;
}

int main()
{
    srand(time(NULL));
    sem_init(&sem_T1, 0, 0);
    sem_init(&sem_T2, 0, 0);

    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread_T1, NULL);
    pthread_create(&t2, NULL, thread_T2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sem_T1);
    sem_destroy(&sem_T2);
    return 0;
}