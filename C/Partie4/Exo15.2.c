#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int tube[2];
    char buffer[512];

    char *ch0 = getenv("ch0");
    char *ch1 = getenv("ch1");

    tube[0] = atoi(ch0);
    tube[1] = atoi(ch1);
    close(tube[1]);

    read(tube[0], buffer, 512);
    printf("\nMessage recu: %s\n", buffer);
    close(tube[0]);

    return 0;
}