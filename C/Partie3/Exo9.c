#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    char path[50];
    char commande[200];
    while (1)
    {
        printf("Repertoire ou copier(taper 1 pour quitter): ");
        fgets(path, 50, stdin);
        path[strcspn(path, "\n")] = '\0';
        if (strcmp(path, "1") == 0)
        {
            exit(0);
        }
        sprintf(commande, "cp -r . %s", path);
        system(commande);
    }
    return 0;
}