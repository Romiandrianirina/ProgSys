#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include<time.h>

int main()
{
    pid_t pid1, pid2;

    pid1 = fork();
    if(pid1 == 0)
    {
        printf("Je suis le fils 1");
        return 0;
    }
    pid2 = fork();
    if(pid2 == 0)
    {
        printf("\nJe suis le fils 2");
    }
    else if(pid2 > 0)
    {
        printf("\nJe suis le pere");
    }
    else
    {
        printf("\nErreur");
    }
    return 0;
}