#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int entier = 0;

void handler(int sig)
{
    FILE *f = fopen("/tmp/entier.txt", "r");
    fscanf(f, "%d", &entier);
    fclose(f);
    printf("Entier reçu : %d\n", entier);
}

int main()
{
    signal(SIGUSR1, handler);
    while (1)
    {
        sleep(1);
    }
    return 0;
}