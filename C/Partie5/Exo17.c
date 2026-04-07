#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void *ma_fonction_thread(void *arg);

int main()
{
    srand(time(NULL));
    int taille = 12;
    int *table = NULL;
    int *resultat;
    pthread_t my_thread;

    pthread_create(&my_thread, NULL, ma_fonction_thread, &taille);
    pthread_join(my_thread, (void **)&resultat);

    for (int i = 0; i < taille; i++)
    {
        printf("- %d\n", resultat[i]);
    }

    return 0;
}

void *ma_fonction_thread(void *arg)
{
    int taille = *(int *)arg;
    int *tab = malloc(taille * sizeof(int));
    for (int i = 0; i < taille; i++)
    {
        tab[i] = rand() % 100;
    }
    return tab;
}