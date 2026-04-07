#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main()
{

    time_t debut,fin;
    int nb_fils = 2;
    pid_t pid;

    debut = time(NULL);
    for (int i = 0; i < nb_fils; i++)
    {
        pid = fork();

        if(pid == 0)
        {
        srand(time(NULL)^i);
        int t = (rand() % 10) + 1;
        printf("veil fils %d pendant: %d secondes\n", i + 1, t);
        sleep(t);
        printf("reveil: fils %d\n",i + 1);
        exit(i);
        }

    }

    for (int i = 0; i < nb_fils; i++)
    {
            wait(NULL);
    }
    fin = time(NULL);
    printf("La duree total est de %ld",(fin-debut));

    return 0;
}