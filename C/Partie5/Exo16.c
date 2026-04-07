#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *ma_fonction_thread(void *arg);

int main()
{
    int ret;
    int table[7] = {1, 2, 3, 4, 5, 6, 7};
    pthread_t my_thread;

    ret = pthread_create(&my_thread, NULL, ma_fonction_thread, table);
    pthread_join(my_thread, NULL);

    return 0;
}

void *ma_fonction_thread(void *arg)
{
    int *table = (int *)arg;
    for (int i = 0; i < 7; i++)
    {
        printf("- %d\n", table[i]);
    }
    pthread_exit(NULL);
}