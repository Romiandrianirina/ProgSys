#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int tube1[2], tube2[2];
    pipe(tube1); // fils->pere pour ecriture invers pour lecture
    pipe(tube2); // pere->fils pour ecriture inverse pour lecture
    pid = fork();
    unsigned char buffer[50];
    int result;

    if (pid == 0)
    {
        close(tube1[0]); // ne lit pas sur le tube1
        close(tube2[1]); // n'ecrit pas sur le tube2

        printf("Le mot que vous recherchez: ");
        fgets(buffer, 50, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        write(tube1[1], buffer, 50);
        close(tube1[1]);

        read(tube2[0], buffer, sizeof(char));
        close(tube2[0]);
        printf("%s\n", buffer);
        result = atoi(buffer);
        printf("%d\n", result);
        if (result)
            printf("Le mot a ete trouve\n");
        else
            printf("Le mot n'existe pas\n");
    }
    else if (pid > 0)
    {
        int valeur = 0;
        FILE *fichier = fopen("texte.txt", "r");
        char *word = malloc(50 * sizeof(char));
        close(tube1[1]); // n'ecrit pas sur le tube1
        close(tube2[0]); // ne lis pas sur le tube2

        dup2(tube1[0], STDIN_FILENO);
        close(tube1[0]);
        fgets(buffer, 50, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        while (fscanf(fichier, "%s", word) == 1)
        {
            if (strcmp(word, buffer) == 0)
            {
                valeur = 1;
                break;
            }
            else
                valeur = 0;
        }
        fclose(fichier);
        dup2(tube2[1], STDOUT_FILENO);
        //  close(tube2[1]);
        // write(tube2[1], &valeur, sizeof(int));
        printf("%d", valeur);
        fflush(stdout);

        wait(NULL);
    }
    return 0;
}