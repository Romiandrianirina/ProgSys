#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int compt = 0;
int limite;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *fonction_incrementeur(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        if (compt >= limite)
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
        compt++;
        printf("Thread 1: compt = %d\n", compt);
        pthread_mutex_unlock(&mutex);

        // attend un temps aléatoire entre 1 et 5 secondes
        int duree = rand() % 5 + 1;
        sleep(duree);
    }
    return NULL;
}

void *fonction_screen(void *arg)
{
    while (1)
    {
        sleep(2); // toutes les 2 secondes

        pthread_mutex_lock(&mutex);
        if (compt >= limite)
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
        printf("Thread 2: compt = %d\n", compt);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char *argv[])
{

    srand(time(NULL));

    pthread_t t1, t2;
    pthread_create(&t1, NULL, fonction_incrementeur, NULL);
    pthread_create(&t2, NULL, fonction_screen, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Valeur limite %d atteinte. Fin du programme.\n", limite);
    pthread_mutex_destroy(&mutex);
    return 0;
}