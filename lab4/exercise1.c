#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

void *checkPrime(void *arg)
{
    int num = *(int *)arg;
    free(arg);

    if (num <= 1)
    {
        return NULL;
    }

    for (int j = 2; j <= sqrt(num); j++)
    {
        if (num % j == 0)
        {
            return NULL;
        }
    }

    printf("%d ", num);
    fflush(stdout);

    return NULL;
}

int main()
{
    pthread_t threads[100];

    for (int i = 0; i < 100; i++)
    {
        int *num_to_check = malloc(sizeof(int));
        *num_to_check = i + 1;

        if (pthread_create(&threads[i], NULL, checkPrime, num_to_check) != 0)
        {
            perror("Failed to create thread");
        }
    }

    for (int i = 0; i < 100; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            perror("Failed to join thread");
        }
    }

    printf("\nAll threads finished.\n");
    return 0;
}