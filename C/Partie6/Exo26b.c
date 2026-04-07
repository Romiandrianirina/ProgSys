#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char nom[100];
    printf("Nom du fichier a charger : ");
    scanf("%s", nom);
    int fd = open(nom, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }
    off_t taille = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    int nb = taille / sizeof(int);
    int *tab = malloc(nb * sizeof(int));
    read(fd, tab, taille);
    close(fd);
    printf("%d entiers lus :\n", nb);
    for (int i = 0; i < nb; i++)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");
    free(tab);
    return 0;
}