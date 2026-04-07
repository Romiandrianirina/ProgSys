#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#define PORT 8888
#define MAX_CLIENTS 10

typedef struct
{
    char ip[16];
    char nom[50];
} Autorisation;

Autorisation *charger_autorisations(int *nb)
{
    FILE *f = fopen("add_autoris.txt", "r");
    if (!f)
        return NULL;
    Autorisation *tab = NULL;
    int cap = 0;
    *nb = 0;
    char ligne[70];
    while (fgets(ligne, sizeof(ligne), f))
    {
        ligne[strcspn(ligne, "\n")] = '\0';
        char *ip = strtok(ligne, " \t");
        char *nom = strtok(NULL, " \t");
        if (!ip || !nom)
            continue;
        if (*nb >= cap)
        {
            cap = cap ? cap * 2 : 10;
            tab = realloc(tab, cap * sizeof(Autorisation));
        }
        strcpy(tab[*nb].ip, ip);
        strcpy(tab[*nb].nom, nom);
        (*nb)++;
    }
    fclose(f);
    return tab;
}

char *trouver_nom(Autorisation *tab, int nb, const char *ip)
{
    for (int i = 0; i < nb; i++)
        if (strcmp(tab[i].ip, ip) == 0)
            return tab[i].nom;
    return NULL;
}

void gerer_client(int sock_client, Autorisation *tab, int nb)
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    getpeername(sock_client, (struct sockaddr *)&addr, &len);
    char *ip_client = inet_ntoa(addr.sin_addr);
    char *nom = trouver_nom(tab, nb, ip_client);
    if (nom)
    {
        char msg[100];
        sprintf(msg, "Bienvenue %s !\n", nom);
        write(sock_client, msg, strlen(msg));
    }
    else
    {
        write(sock_client, "Acces non autorise.\n", 20);
    }
    close(sock_client);
}

int main()
{
    int nb;
    Autorisation *autorisations = charger_autorisations(&nb);
    if (!autorisations)
    {
        fprintf(stderr, "Erreur chargement add_autoris.txt\n");
        return 1;
    }
    int sock_ecoute = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_ecoute < 0)
    {
        perror("socket");
        return 1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sock_ecoute, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        return 1;
    }
    listen(sock_ecoute, MAX_CLIENTS);
    signal(SIGCHLD, SIG_IGN);
    printf("Serveur en ecoute sur port %d\n", PORT);
    while (1)
    {
        int sock_client = accept(sock_ecoute, NULL, NULL);
        if (sock_client < 0)
        {
            perror("accept");
            continue;
        }
        if (fork() == 0)
        {
            close(sock_ecoute);
            gerer_client(sock_client, autorisations, nb);
            exit(0);
        }
        close(sock_client);
    }
    free(autorisations);
    close(sock_ecoute);
    return 0;
}