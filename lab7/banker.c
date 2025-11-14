#include <stdio.h>
int main()
{
    int allocation[5][4] = {
        {0, 0, 1, 2},
        {1, 0, 0, 0},
        {1, 3, 5, 4},
        {0, 6, 3, 2},
        {0, 0, 1, 4}};

    int max[5][4] = {
        {0, 0, 1, 2},
        {1, 7, 5, 0},
        {2, 3, 5, 6},
        {0, 6, 5, 2},
        {0, 6, 5, 6}};

    int available[4] = {1, 5, 2, 0};
    int available_t[4];
    int allocation_t[5][4];
    for (int i = 0; i < 4; i++)
    {
        available_t[i] = available[i];
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            allocation_t[i][j] = allocation[i][j];
        }
    }
    int need[5][4];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    printf("need matrice: \n");
    for (int i = 0; i < 5; i++)
    {
        // printf("P%d \n", i);
        for (int j = 0; j < 4; j++)
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    int finish[5] = {0};
    int count = 0;
    while (count < 5)
    {
        int found = 0;
        for (int i = 0; i < 5; i++)
        {
            if (!finish[i])
            {
                int j;
                for (j = 0; j < 4; j++)
                {
                    if (need[i][j] > available[j])
                    {
                        break;
                    }
                }
                if (j == 4)
                {
                    printf("P%d\n", i);
                    for (int k = 0; k < 4; k++)
                    {
                        available[k] += allocation[i][k];
                    }
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }
        if (!found)
        {
            printf("The system is not in safe state\n");
            break;
        }
    }
    printf("\n--testing p1 request--\n");
    for (int i = 0; i < 4; i++)
    {
        available[i] = available_t[i];
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            allocation[i][j] = allocation_t[i][j];
        }
    }
    int request[4] = {0, 4, 2, 0};
    int p = 1;
    int can_grant = 1;
    for (int j = 0; j < 4; j++)
    {
        if (request[j] > need[p][j])
        {
            printf("Request exceeds p1's need\n");
            can_grant = 0;
            break;
        }
        if (request[j] > available[j])
        {
            printf("not enough available resources\n");
            can_grant = 0;
            break;
        }
    }

    if (can_grant)
    {
        // Pretend to allocate
        for (int j = 0; j < 4; j++)
        {
            available[j] -= request[j];
            allocation[p][j] += request[j];
            need[p][j] -= request[j];
        }

        // Re-run safety test
        int finish2[5] = {0};
        int count2 = 0;
        int found_safe = 0;
        while (count2 < 5)
        {
            int found = 0;
            for (int i = 0; i < 5; i++)
            {
                if (!finish2[i])
                {
                    int j;
                    for (j = 0; j < 4; j++)
                        if (need[i][j] > available[j])
                            break;
                    if (j == 4)
                    {
                        for (int k = 0; k < 4; k++)
                            available[k] += allocation[i][k];
                        finish2[i] = 1;
                        count2++;
                        found = 1;
                    }
                }
            }
            if (!found)
                break;
        }
        if (count2 == 5)
            printf("P1's request can be granted safely.\n");
        else
            printf("P1's request would lead to an unsafe state.\n");
    }
}