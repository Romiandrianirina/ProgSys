#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include<time.h>

int main()
{
    int nb_fils = 5;
    pid_t pid;

    for (int i = 0; i < nb_fils; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            printf("Je suis le fils %d\n", i + 1);
            break;
        }
    }
    return (0);
}