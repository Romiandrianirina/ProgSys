#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>

#define PORT 8080
#define BUFFER_SIZE 256

typedef struct
{
    char nom[50];
    float prix;
} Produit;

Produit *charger_produits(const char *fichier, int *nb)
{
    FILE *f = fopen(fichier, "r");
    if (!f)
    {
        perror("fopen");
        return NULL;
    }
    Produit *tab = NULL;
    int cap = 0;
    *nb = 0;
    char ligne[100];
    while (fgets(ligne, sizeof(ligne), f))
    {
        if (ligne[strlen(ligne) - 1] == '\n')
            ligne[strlen(ligne) - 1] = '\0';
        char *nom = strtok(ligne, " ");
        char *prix_str = strtok(NULL, " ");
        if (!nom || !prix_str)
            continue;
        if (*nb >= cap)
        {
            cap = cap ? cap * 2 : 10;
            tab = realloc(tab, cap * sizeof(Produit));
        }
        strcpy(tab[*nb].nom, nom);
        tab[*nb].prix = atof(prix_str);
        (*nb)++;
    }
    fclose(f);
    return tab;
}

Produit *chercher_produit(Produit *tab, int nb, const char *nom)
{
    for (int i = 0; i < nb; i++)
        if (strcmp(tab[i].nom, nom) == 0)
            return &tab[i];
    return NULL;
}

void enregistrer_commande(const char *nom_client, const char *details, float total)
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char filename[100];
    strftime(filename, sizeof(filename), "commande_%Y-%m-%d_%H:%M:%S.txt", tm);
    FILE *f = fopen(filename, "w");
    if (!f)
    {
        perror("fopen");
        return;
    }
    fprintf(f, "Client : %s\n", nom_client);
    fprintf(f, "Details : %s\n", details);
    fprintf(f, "Total : %.2f €\n", total);
    fclose(f);
    printf("Commande enregistree dans %s\n", filename);
}

void gerer_client(int sock, Produit *cat, int nb_prod)
{
    char buffer[BUFFER_SIZE];
    char details[1024] = "";
    float total = 0.0;

    write(sock, "Entrez produit et quantite (ex: pomme 3). Ligne vide pour finir :\n", 65);
    while (1)
    {
        int n = read(sock, buffer, sizeof(buffer) - 1);
        if (n <= 0)
            break;
        buffer[n - 1] = '\0';
        if (strlen(buffer) == 0)
            break;
        char *nom = strtok(buffer, " ");
        char *qte_str = strtok(NULL, " ");
        if (!nom || !qte_str)
        {
            write(sock, "Format incorrect. Exemple: pomme 3\n", 35);
            continue;
        }
        Produit *p = chercher_produit(cat, nb_prod, nom);
        if (!p)
        {
            write(sock, "Produit inconnu.\n", 17);
            continue;
        }
        int qte = atoi(qte_str);
        total += p->prix * qte;
        char ligne[100];
        sprintf(ligne, "%s x%d = %.2f\n", nom, qte, p->prix * qte);
        strcat(details, ligne);
    }
    write(sock, "Votre nom : ", 12);
    int n = read(sock, buffer, sizeof(buffer) - 1);
    char nom_client[50];
    if (n > 0)
    {
        buffer[n - 1] = '\0';
        strcpy(nom_client, buffer);
    }
    else
    {
        strcpy(nom_client, "anonyme");
    }
    char reponse[256];
    sprintf(reponse, "Total de la commande : %.2f €\n", total);
    write(sock, reponse, strlen(reponse));
    enregistrer_commande(nom_client, details, total);
    close(sock);
}

int main()
{
    int nb_prod;
    Produit *catalogue = charger_produits("produits.txt", &nb_prod);
    if (!catalogue)
    {
        fprintf(stderr, "Erreur chargement produits\n");
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
    listen(sock_ecoute, 5);
    printf("Serveur en ecoute sur port %d\n", PORT);

    signal(SIGCHLD, SIG_IGN); // eviter les zombies

    while (1)
    {
        struct sockaddr_in client_addr;
        socklen_t len = sizeof(client_addr);
        int sock_client = accept(sock_ecoute, (struct sockaddr *)&client_addr, &len);
        if (sock_client < 0)
        {
            perror("accept");
            continue;
        }
        pid_t pid = fork();
        if (pid == 0)
        {
            close(sock_ecoute);
            gerer_client(sock_client, catalogue, nb_prod);
            exit(0);
        }
        else
        {
            close(sock_client);
        }
    }
    free(catalogue);
    close(sock_ecoute);
    return 0;
}