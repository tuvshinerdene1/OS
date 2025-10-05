#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 10

int a[MAX][MAX];
int b[MAX][MAX];
int c[MAX][MAX];
int r1, c1, r2, c2;

typedef struct
{
    int row;
    int col;
} ThreadData;

void *calculate(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    int sum = 0;
    ;
    for (int i = 0; i < c1; i++)
    {
        sum += a[data->row][i] * b[i][data->col];
    }
    c[data->row][data->col] = sum;
    free(data);
    pthread_exit(0);
};
int main()
{
    printf("a row = ");
    scanf("%d", &r1);
    printf("a column = ");
    scanf("%d", &c1);
    printf("b row = ");
    scanf("%d", &r2);
    printf("b column = ");
    scanf("%d", &c2);
    if (c1 != r2 || r1 > MAX || c1 > MAX || r2 > MAX || c2 > MAX)
    {
        printf("Invalid rows and columns!");
        return 1;
    }
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c1; j++)
        {
            printf("a[%d][%d] = ", i, j);
            scanf("%d", &a[i][j]);
        }
    }
    for (int i = 0; i < r2; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            printf("b[%d][%d] = ", i, j);
            scanf("%d", &b[i][j]);
        }
    }

    pthread_t threads[MAX * MAX];
    int thread_count = 0;
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            ThreadData *data = (ThreadData *)malloc(sizeof(ThreadData));
            data->col = j;
            data->row = i;

            pthread_create(&threads[thread_count++], NULL, calculate, data);
        }
    }
    for (int i = 0; i < thread_count; i++)
    {
        pthread_join(threads[i], NULL);
    }
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    return 0;
}
