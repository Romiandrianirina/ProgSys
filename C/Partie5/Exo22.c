#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int compteur = 0;
double u = 1.0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

double f1(double x)
{
    return (x - 1) * (x - 1) / 4.0;
}

double f2(double x)
{
    return (x - 2) * (x - 2) / 6.0;
}

void *thread_T1(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        u = f1(u);
        compteur++;
        printf("T1: u = %f, iterations = %d\n", u, compteur);
        pthread_mutex_unlock(&mutex);
        int duree = rand() % 5 + 1;
        sleep(duree);
    }
    return NULL;
}

void *thread_T2(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        u = f2(u);
        compteur++;
        printf("T2: u = %f, iterations = %d\n", u, compteur);
        pthread_mutex_unlock(&mutex);
        int duree = rand() % 5 + 1;
        sleep(duree);
    }
    return NULL;
}

int main()
{
    srand(time(NULL));
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread_T1, NULL);
    pthread_create(&t2, NULL, thread_T2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}