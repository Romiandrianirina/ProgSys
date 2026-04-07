#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8082
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s repertoire\n", argv[0]);
        exit(1);
    }
    const char *repertoire = argv[1];
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "tar czf /tmp/rep.tgz -C %s .", repertoire);
    if (system(cmd) != 0)
    {
        fprintf(stderr, "Erreur lors de la creation de l'archive\n");
        exit(1);
    }
    FILE *f = fopen("/tmp/rep.tgz", "rb");
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
    shutdown(sock, SHUT_WR);
    n = read(sock, buffer, sizeof(buffer) - 1);
    if (n > 0)
    {
        buffer[n] = '\0';
        if (strcmp(buffer, "OK\n") == 0)
            printf("Repertoire copie avec succes.\n");
        else
            printf("Erreur lors de la copie.\n");
    }
    close(sock);
    unlink("/tmp/rep.tgz");
    return 0;
}