#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int tube[2];
    char buffer[512];

    tube[0] = atoi(argv[1]);
    tube[1] = atoi(argv[2]);

    close(tube[1]);

    read(tube[0], buffer, 512);
    printf("\nMessage recu: %s\n", buffer);
    close(tube[0]);

    return 0;
}