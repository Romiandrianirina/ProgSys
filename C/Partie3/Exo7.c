#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    execlp("cp","cp", "-R","." , argv[1], NULL);

    return 0;
}