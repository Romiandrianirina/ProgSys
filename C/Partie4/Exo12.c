#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int tube1[2], tube2[2];
    pipe(tube1);
    pipe(tube2);
    pid = fork();
    unsigned char buffer[50];
    int result;

    if (pid == 0)
    {
        close(tube1[0]);
        close(tube2[1]);
        printf("Le mot que vous recherchez: ");
        fgets(buffer, 50, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        write(tube1[1], buffer, 50);
        read(tube2[0], &result, sizeof(int));
        if (result)
            printf("Le mot a ete trouve\n");
        else
            printf("Le mot n'existe pas\n");
    }
    else if (pid > 0)
    {
        int valeur;
        FILE *fichier = fopen("texte.txt", "r");
        char *word = malloc(50 * sizeof(char));
        close(tube1[1]);
        close(tube2[0]);
        read(tube1[0], buffer, 50);
        while (fscanf(fichier,"%s",word) == 1)
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
        write(tube2[1], &valeur, sizeof(int));
        wait(NULL);
    }
        return 0;
}