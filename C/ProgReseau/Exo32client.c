#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8081
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s chemin_fichier\n", argv[0]);
        exit(1);
    }
    const char *chemin = argv[1];
    FILE *f = fopen(chemin, "r");
    if (!f)
    {
        perror("fopen");
        exit(1);
    }
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket");
        exit(1);
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(1);
    }
    char buffer[BUFFER_SIZE];
    int n;
    while ((n = fread(buffer, 1, sizeof(buffer), f)) > 0)
    {
        write(sock, buffer, n);
    }
    fclose(f);
    shutdown(sock, SHUT_WR); // signale la fin des données
    // Lire la réponse du serveur
    n = read(sock, buffer, sizeof(buffer) - 1);
    if (n > 0)
    {
        buffer[n] = '\0';
        if (strcmp(buffer, "OK\n") == 0)
            printf("Fichier copie avec succes.\n");
        else
            printf("Erreur lors de la copie.\n");
    }
    close(sock);
    return 0;
}