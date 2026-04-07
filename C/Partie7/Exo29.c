#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void fils_mourant(int sig)
{
    printf("Fils %d terminé\n", getpid());
    exit(0);
}

int main()
{
    pid_t fils[5];
    for (int i = 0; i < 5; i++)
    {
        fils[i] = fork();
        if (fils[i] == 0)
        {
            signal(SIGTERM, fils_mourant);
            while (1)
                pause();
        }
    }
    int choix, num;
    while (1)
    {
        printf("1-Endormir, 2-Réveiller, 3-Terminer, 4-Quitter\n");
        scanf("%d", &choix);
        if (choix == 4)
            break;
        printf("Numéro du fils (1-5) : ");
        scanf("%d", &num);
        if (num < 1 || num > 5)
            continue;
        if (choix == 1)
            kill(fils[num - 1], SIGSTOP);
        else if (choix == 2)
            kill(fils[num - 1], SIGCONT);
        else if (choix == 3)
            kill(fils[num - 1], SIGTERM);
    }
    for (int i = 0; i < 5; i++)
        kill(fils[i], SIGTERM);
    while (wait(NULL) > 0)
        ;
    return 0;
}