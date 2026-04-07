#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
// a)
typedef struct
{
    int *T1;
    int taille1;
    int *T2;
    int taille2;
} PourComparaison;

void *fonction_annulation(void *arg);
void *fonction_T(void *arg);
void *fonction_comparaison(void *arg);

int main()
{
    srand(time(NULL));
    pthread_t annulation, T1, T2, comparaison;
    int taille1 = 2, taille2 = 40;
    int *tab1, *tab2;
    PourComparaison P;
    P.T1 = tab1;
    P.T2 = tab2;
    P.taille1 = taille1;
    P.taille2 = taille2;

    pthread_create(&annulation, NULL, fonction_annulation, NULL);

    pthread_create(&T1, NULL, fonction_T, &taille1);
    pthread_create(&T2, NULL, fonction_T, &taille2);

    pthread_join(T1, (void **)&tab1);
    pthread_join(T2, (void **)&tab2);

    P.T1 = tab1;
    P.T2 = tab2;

    pthread_create(&comparaison, NULL, fonction_comparaison, &P);

    pthread_join(comparaison, NULL);
    //pthread_join(annulation, NULL);
    printf("\n\n\nRETOUR\n\n\n");
    exit(0);

    free(tab1);
    free(tab2);
    return 0;
}

void *fonction_annulation(void *arg)
{
    char Valeur;
    printf("\n------Appuyer sur A pour annuler l'operation------\n");
    scanf("%c", &Valeur);
    getchar();
    if (Valeur == 'A' || Valeur == 'a')
    {
        printf("Annulation du programme\n");
        exit(0);
    }
    return NULL;
}

void *fonction_T(void *arg)
{
    int taille = *(int *)arg;
    int *tab = malloc(taille * sizeof(int));
    for (int i = 0; i < taille; i++)
    {
        tab[i] = rand() % 100;
    }
    return tab;
}

void *fonction_comparaison(void *arg)
{
    sleep(3);
    PourComparaison *Q = (PourComparaison *)arg;
    int inclus = 1;
    for (int i = 0; i < Q->taille1; i++)
    {
        int trouve = 0;
        for (int j = 0; j < Q->taille2; j++)
        {
            if (Q->T1[i] == Q->T2[j])
            {
                trouve = 1;
                break;
            }
        }
        if (!trouve)
        {
            inclus = 0;
            break;
        }
    }
    printf("\n\nT1 =");
    for (int i = 0; i < Q->taille1; i++)
    {
        printf(" %d", Q->T1[i]);
    }
    printf("\n\nT2 =");
    for (int i = 0; i < Q->taille2; i++)
    {
        printf(" %d", Q->T2[i]);
    }
    if (inclus)
    {
        printf("\n\nT1 inclus dans T2\n");
    }
    else
    {
        printf("\n\nT1 non inclus dans T2\n");
    }
        pthread_exit(NULL);
}
// b) La complexite de l'algorythne est O(|T1|x|T2|)