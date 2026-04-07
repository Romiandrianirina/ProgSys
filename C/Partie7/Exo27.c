#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    if (pid == 0)
    {
        while (1)
            ;
    }
    else
    {
        char c;
        do
        {
            printf("Menu: s (endormir), r (réveiller), q (quitter)\n");
            scanf(" %c", &c);
            if (c == 's')
            {
                kill(pid, SIGSTOP);
            }
            else if (c == 'r')
            {
                kill(pid, SIGCONT);
            }
            else if (c == 'q')
            {
                kill(pid, SIGTERM);
                wait(NULL);
                break;
            }
        } while (1);
    }
    return 0;
}