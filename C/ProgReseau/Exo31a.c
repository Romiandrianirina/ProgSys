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

int ip_autorisee(const char *ip)
{
    FILE *f = fopen("add_autoris.txt", "r");
    if (!f)
        return 0;
    char ligne[20];
    while (fgets(ligne, sizeof(ligne), f))
    {
        ligne[strcspn(ligne, "\n")] = '\0';
        if (strcmp(ligne, ip) == 0)
        {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void gerer_client(int sock_client)
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    getpeername(sock_client, (struct sockaddr *)&addr, &len);
    char *ip_client = inet_ntoa(addr.sin_addr);
    if (ip_autorisee(ip_client))
    {
        write(sock_client, "Connexion autorisee.\n", 21);
    }
    else
    {
        write(sock_client, "Acces refuse.\n", 14);
        close(sock_client);
        exit(0);
    }
    close(sock_client);
}

int main()
{
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
            gerer_client(sock_client);
            exit(0);
        }
        close(sock_client);
    }
    close(sock_ecoute);
    return 0;
}