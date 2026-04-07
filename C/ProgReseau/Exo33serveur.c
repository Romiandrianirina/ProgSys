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

#define PORT 8082
#define BUFFER_SIZE 1024

void sauvegarder_archive(int sock_client, struct sockaddr_in client_addr)
{
    char *ip_client = inet_ntoa(client_addr.sin_addr);
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char archive_name[256];
    snprintf(archive_name, sizeof(archive_name),
             "/tmp/archive_%s_%04d_%02d_%02d_%02d%02d%02d.tgz",
             ip_client, tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
             tm->tm_hour, tm->tm_min, tm->tm_sec);
    FILE *f = fopen(archive_name, "wb");
    if (!f)
    {
        perror("fopen");
        write(sock_client, "ERR\n", 4);
        return;
    }
    char buffer[BUFFER_SIZE];
    int n;
    while ((n = read(sock_client, buffer, sizeof(buffer))) > 0)
    {
        fwrite(buffer, 1, n, f);
    }
    fclose(f);
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "cd /home/save && tar zxvf %s 2>/dev/null", archive_name);
    int ret = system(cmd);
    unlink(archive_name);
    if (ret == 0)
        write(sock_client, "OK\n", 3);
    else
        write(sock_client, "ERR\n", 4);
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
    listen(sock_ecoute, 5);
    signal(SIGCHLD, SIG_IGN);
    printf("Serveur en ecoute sur port %d\n", PORT);
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
        if (fork() == 0)
        {
            close(sock_ecoute);
            sauvegarder_archive(sock_client, client_addr);
            exit(0);
        }
        close(sock_client);
    }
    close(sock_ecoute);
    return 0;
}