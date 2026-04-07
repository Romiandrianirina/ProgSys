#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    int n;
    printf("Entrez un entier : ");
    scanf("%d", &n);
    FILE *f = fopen("/tmp/entier.txt", "w");
    fprintf(f, "%d", n);
    fclose(f);
    kill(0, SIGUSR1);
    return 0;
}