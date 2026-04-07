#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define N 100

double tableau[N];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_moyenne(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        double copie[N];
        for (int i = 0; i < N; i++)
            copie[i] = tableau[i];
        for (int i = 1; i <= N - 2; i++)
        {
            tableau[i] = (copie[i - 1] + copie[i] + copie[i + 1]) / 3.0;
        }
        pthread_mutex_unlock(&mutex);
        int duree = rand() % 3 + 1;
        sleep(duree);
    }
    return NULL;
}

void *thread_affiche(void *arg)
{
    while (1)
    {
        sleep(4);
        pthread_mutex_lock(&mutex);
        printf("Tableau : ");
        for (int i = 0; i < N; i++)
            printf("%.2f ", tableau[i]);
        printf("\n");
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        if (i == 0 || i == N - 1)
            tableau[i] = 0.0;
        else
            tableau[i] = (double)(rand() % 101);
    }
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread_moyenne, NULL);
    pthread_create(&t2, NULL, thread_affiche, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}