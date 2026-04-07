#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

jmp_buf env;

void segfault_handler(int sig)
{
    longjmp(env, 1);
}

int main()
{
    signal(SIGSEGV, segfault_handler);
    int n;
    printf("Nombre d'éléments : ");
    scanf("%d", &n);
    int *tab = malloc(n * sizeof(int));
    printf("Entrez %d entiers :\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &tab[i]);
    int i;
    while (1)
    {
        printf("Indice à afficher : ");
        scanf("%d", &i);
        if (setjmp(env) == 0)
        {
            printf("tab[%d] = %d\n", i, tab[i]);
            break;
        }
        else
        {
            printf("Erreur de segmentation, réessayez\n");
        }
    }
    free(tab);
    return 0;
}