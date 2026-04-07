#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include<time.h>

int main()
{
    pid_t pid;
    pid = fork();
    if (pid == 0)
    {
        printf("On est dans le processus enfant\n");
    }
    else if (pid > 0)
    {
        printf("On est dans le processus pere\n");
    }
    else
    {
        fprintf(stderr, "Error\n");
        exit(1);
    }
    return 0;
}