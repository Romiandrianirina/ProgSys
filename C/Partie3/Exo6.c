#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    if(argc == 0)
    {
        printf("Aucun argument entre\n");
        exit(0);
    }
    else if(argc > 0 && argc > 3)
    {
        printf("Trop d'argument\n");
        exit(0);
    }
    else if(argc == 2)
    {
        printf("Un argument manquant\n");
        exit (0);
    }
    else if(argc > 0 && argc == 3)
    {
        int a, b;
        a = atoi(argv[1]);
        b = atoi(argv[2]);
        printf("%d + %d = %d\n",a,b,a+b);
    }
    else
    {
        printf("Erreur\n");
    }

    return 0;
}