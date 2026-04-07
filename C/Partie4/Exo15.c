#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    pid_t pid_fils;
    int tube[2];
    pipe(tube);
    char buffer[512] = {"Voici un message pour mon fils"};
    pid_fils = fork();

    if (pid_fils == 0)
    {
        char ch0[20],ch1[20];
        snprintf(ch0, 20,"%d",tube[0]);
        snprintf(ch1, 20,"%d",tube[1]);

        setenv("ch0",ch0, 1);
        setenv("ch1", ch1,1);

        char *argv[] = {"./Exo15.2", NULL};
        execv(argv[0], argv);
    }
    else if (pid_fils > 0)
    {
        printf("Message envoye: %s\n", buffer);
        close(tube[0]);
        write(tube[1], buffer, 512);
        close(tube[1]);
        wait(NULL);
    }

    return 0;
}