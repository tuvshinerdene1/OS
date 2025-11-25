#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int compare_ints(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
long SSTF(int *request, int start)
{
    int visited[1000] = {0};
    int current = start;
    long total = 0;
    for (int served = 0; served < 1000; served++)
    {
        int min_dist = 9999999;
        int index = -1;
        for (int i = 0; i < 1000; i++)
        {
            if (!visited[i])
            {
                int dist = abs(request[i] - current);
                if (dist < min_dist)
                {
                    min_dist = dist;
                    index = i;
                }
            }
        }
        visited[index] = 1;
        total += abs(current - request[index]);
        current = request[index];
    }

    return total;
}

long FCFS(int *request, int start)
{
    long result = abs(start - request[0]);
    for (int i = 1; i < 1000; i++)
    {
        result += abs(request[i] - request[i - 1]);
    }
    return result;
}
long SCAN(int *request, int start)
{
    qsort(request, 1000, sizeof(int), compare_ints);
    int i;
    long result = 0;
    for (i = 0; i < 1000; i++)
    {
        if (request[i] > start)
        {
            break;
        }
    }
    if (i == 0)
    {
        result += abs(start - request[0]);
        for (int j = 0; j < 999; j++)
        {
            result += abs(request[j] - request[j + 1]);
        }
        return result;
    }
    result += abs(start - request[i - 1]);
    for (int j = i - 1; j > 0; j--)
    {
        result += abs(request[j] - request[j - 1]);
    }
    result += request[0] - 0;
    result += request[i];
    for (int j = i; j < 999; j++)
    {
        result += abs(request[j] - request[j + 1]);
    }
    return result;
}
long CSCAN(int *request, int start)
{
    qsort(request, 1000, sizeof(int), compare_ints);
    int i;
    long result = 0;
    for (i = 0; i < 1000; i++)
    {
        if (request[i] > start)
        {
            break;
        }
    }
    if (i == 0)
    {
        result += abs(start - request[0]);
        for (int j = 0; j < 999; j++)
        {
            result += abs(request[j] - request[j + 1]);
        }
        return result;
    }
    result += request[i] - start;
    for (int j = i; j < 999; j++)
    {
        result += abs(request[j] - request[j + 1]);
    }
    result += 5000 - request[999];
    result += 5000;
    result += request[0] - 0;
    for (int j = 0; j < i - 1; j++)
    {
        result += abs(request[j] - request[j + 1]);
    }
    return result;
}
int main()
{
    srand(time(0));
    int min = 0;
    int max = 5000;

    int *request = (int *)malloc(1000 * sizeof(int));
    int *req_copy1 = (int *)malloc(1000 * sizeof(int));
    int *req_copy2 = (int *)malloc(1000 * sizeof(int));
    int *req_copy3 = (int *)malloc(1000 * sizeof(int));

    for (int i = 0; i < 1000; i++)
    {
        request[i] = (rand() % (max - min + 1)) + min;
    }
    memcpy(req_copy1, request, 1000 * sizeof(int));
    memcpy(req_copy2, request, 1000 * sizeof(int));
    memcpy(req_copy3, request, 1000 * sizeof(int));

    int start;
    printf("start = ");
    scanf("%d", &start);

    long result;

    result = SCAN(request, start);
    printf("SCAN : %ld\n", result);

    result = FCFS(req_copy1, start);
    printf("FCFS : %ld\n", result);

    result = CSCAN(req_copy2, start);
    printf("CSCAN : %ld\n", result);

    result = SSTF(req_copy3, start);
    printf("SSTF : %ld\n", result);

    free(request);
    free(req_copy1);
    free(req_copy2);
    free(req_copy3);

    return 0;
}