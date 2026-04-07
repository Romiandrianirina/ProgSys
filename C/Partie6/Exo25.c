#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s repertoire1 [repertoire2 ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++)
    {
        const char *rep = argv[i];
        DIR *dir = opendir(rep);
        if (dir == NULL)
        {
            perror("opendir");
            continue;
        }

        printf("Répertoire : %s\n", rep);
        struct dirent *entree;
        while ((entree = readdir(dir)) != NULL)
        {
            if (strcmp(entree->d_name, ".") == 0 || strcmp(entree->d_name, "..") == 0)
                continue;

            char chemin_complet[1024];
            snprintf(chemin_complet, sizeof(chemin_complet), "%s/%s", rep, entree->d_name);

            struct stat infos;
            if (stat(chemin_complet, &infos) == -1)
            {
                perror("stat");
                continue;
            }

            if (S_ISREG(infos.st_mode) && infos.st_size > 1000000)
            {
                printf("  %s (taille: %ld octets, UID: %d)\n",
                       entree->d_name, infos.st_size, infos.st_uid);
            }
        }
        closedir(dir);
        printf("\n");
    }
    return 0;
}