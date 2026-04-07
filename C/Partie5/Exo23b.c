#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

int N;         // nombre de threads (passé en argument)
int count = 0; // compteur d'arrivée
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t barriere; // sémaphore pour bloquer les threads

void *thread_rdv(void *arg)
{
    int id = *(int *)arg;
    free(arg);
    for (int iter = 1; iter <= 5; iter++)
    {
        int duree = rand() % 5 + 1; // entre 1 et 5 secondes
        printf("Thread %d : début itération %d, durée %d s\n", id, iter, duree);
        sleep(duree);
        printf("Thread %d : fin itération %d, attente des autres\n", id, iter);

        // Barrière
        pthread_mutex_lock(&mutex);
        count++;
        if (count == N)
        {
            // dernier thread : libère les N-1 autres
            for (int i = 0; i < N - 1; i++)
                sem_post(&barriere);
            count = 0;
            pthread_mutex_unlock(&mutex);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
            sem_wait(&barriere);
        }
    }
    printf("Thread %d terminé\n", id);
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s N\n", argv[0]);
        exit(1);
    }
    N = atoi(argv[1]);
    if (N <= 0)
        exit(1);

    srand(time(NULL));
    sem_init(&barriere, 0, 0);

    pthread_t *threads = malloc(N * sizeof(pthread_t));
    for (int i = 0; i < N; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&threads[i], NULL, thread_rdv, id);
    }
    for (int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    free(threads);
    sem_destroy(&barriere);
    pthread_mutex_destroy(&mutex);
    return 0;
}