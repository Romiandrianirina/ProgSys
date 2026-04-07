#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    char fichier[50];
    char commande[200];
    while (1)
    {
        printf("Fichier a ouvrir(taper 1 pour arreter): ");
        fgets(fichier, 50, stdin);
        fichier[strcspn(fichier, "\n")] = '\0';
        if (strcmp(fichier, "1") == 0)
        {
            exit(0);
        }
        sprintf(commande, "emacs %s &", fichier);
        system(commande);
    }
    return 0;
}