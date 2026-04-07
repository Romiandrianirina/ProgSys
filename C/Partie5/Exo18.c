#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct
{
    int *table;
    int taille;
    int x;
} TypeTableau;

void *fonction_thread1(void *arg2)
{
    int size = *(int *)arg2;
    TypeTableau *k = malloc(sizeof(TypeTableau));
    k->taille = size;
    k->table = malloc(k->taille * sizeof(int));
    for (int i = 0; i < k->taille; i++)
    {
        k->table[i] = rand() % 100;
    }

    return k;
}

void *fonction_thread2(void *arg)
{
    TypeTableau *k = (TypeTableau *)arg;
    for (int i = 0; i < k->taille; i++)
    {
        if (k->table[i] == k->x)
            return (void *)1;
    }
    return (void *)0;
}

int main()
{
    srand(time(NULL));
    int taille = 12;
    int verify;
    TypeTableau *tab1;
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, fonction_thread1, &taille);
    pthread_join(thread1, (void **)&tab1);

    printf("Valeur a rechercher: ");
    scanf("%d", &tab1->x);

    for (int i = 0; i < tab1->taille; i++)
    {
        printf("-%d\n", tab1->table[i]);
    }

    int ret = pthread_create(&thread2, NULL, fonction_thread2, tab1);
    if (ret != 0)
    {
        fprintf(stderr, "Erreur de cr�ation du thread");
        exit(1);
    }
    pthread_join(thread2, (void **)&verify);

    if (verify)
        printf("Il est bien present\n");
    else
        printf("Il n'est pas present\n");

    free(tab1->table);
    free(tab1);
    return 0;
}