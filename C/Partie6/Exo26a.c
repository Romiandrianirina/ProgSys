#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int n;
    printf("Nombre d'entiers : ");
    scanf("%d", &n);
    int *tab = malloc(n * sizeof(int));
    printf("Entrez les %d entiers :\n", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &tab[i]);
    }
    char nom[100];
    printf("Nom du fichier de sauvegarde : ");
    scanf("%s", nom);
    int fd = open(nom, O_WRONLY | O_CREAT | O_TRUNC, 0624);
    if (fd == -1)
    {
        perror("open");
        free(tab);
        exit(1);
    }
    write(fd, tab, n * sizeof(int));
    close(fd);
    free(tab);
    return 0;
}