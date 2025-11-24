#include <stdio.h>

int is_including(int *arr, int size, int num)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == num)
            return 1; // found (page hit)
    }
    return 0; // not found (page fault)
}

void print_frames(int *frames, int frame_count)
{
    for (int i = 0; i < 3; i++)
    {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}
void FIFO(int *reference_string, int n)
{
    printf("FIFO algorithm \n");
    int frames[3];
    int page_faults = 0;
    int index = 0;

    for (int i = 0; i < 3; i++)
        frames[i] = -1;

    printf("Reference | Frames State\n");
    printf("----------|----------------\n");

    for (int i = 0; i < n; i++)
    {
        int page = reference_string[i];

        printf("%4d      | ", page);

        if (is_including(frames, 3, page))
        {
            print_frames(frames, 3);
            continue;
        }

        page_faults++;

        frames[index] = page;

        index = (index + 1) % 3;

        print_frames(frames, 3);
    }

    printf("\nTotal Page Faults (FIFO): %d\n", page_faults);
}

int find_index(int *arr, int begin, int size, int num)
{
    for (int i = begin + 1; i < size; i++)
    {
        if (arr[i] == num)
        {
            return i;
        }
    }
    return size;
}
int find_index_backwards(int *arr, int begin, int num)
{
    for (int i = begin; i >= 0; i--)
    {
        if (arr[i] == num)
        {
            return i;
        }
    }
    return -1;
}
int count_occupied(int *arr, int size)
{
    int occupied = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] >= 0)
        {
            occupied++;
        }
    }
    return occupied;
}

void OPT(int *reference_string, int n)
{
    printf("OPT algorithm:\n");
    int frames[3];
    int page_faults = 0;
    int index = 0;
    for (int i = 0; i < 3; i++)
        frames[i] = -1;
    printf("Reference | Frames State\n");
    printf("----------|----------------\n");

    for (int i = 0; i < n; i++)
    {
        int page = reference_string[i];
        if (is_including(frames, 3, page))
        {
            continue;
        }
        page_faults++;
        int filled = count_occupied(frames, 3);
        if (filled < 3)
        {
            frames[filled] = page;
            continue;
        }
        // replacement logic here
        int furthest_index = 0;
        for (int j = 1; j < 3; j++)
        {
            if (find_index(reference_string, i, n, frames[j]) > find_index(reference_string, i, n, frames[furthest_index]))
            {
                furthest_index = j;
            }
        }
        frames[furthest_index] = page;
        print_frames(frames, 3);
    }
    printf("\nTotal Page Faults (OPT): %d\n", page_faults);
}
void LRU(int *reference_string, int n)
{
    printf("LRU algorithm:\n");
    int frames[3];
    int page_faults = 0;
    int index = 0;
    for (int i = 0; i < 3; i++)
    {
        frames[i] = -1;
    }
    printf("Reference | Frames State\n");
    printf("----------|----------------\n");
    for (int i = 0; i < n; i++)
    {
        int page = reference_string[i];
        if (is_including(frames, 3, page))
        {
            continue;
        }
        page_faults++;
        int filled = count_occupied(frames, 3);
        if (filled < 3)
        {
            frames[filled] = page;
            continue;
        }
        // replacement logic here
        int least_recent = 0;
        for (int j = 1; j < 3; j++)
        {
            if (find_index_backwards(reference_string, i - 1, frames[least_recent]) > find_index_backwards(reference_string, i - 1, frames[j]))
            {
                least_recent = j;
            }
        }
        frames[least_recent] = page;
        print_frames(frames, 3);
    }
    printf("\nTotal Page Faults (LRU): %d\n", page_faults);
}
int main()
{
    int reference_string[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int n = sizeof(reference_string) / sizeof(reference_string[0]);
    FIFO(reference_string, n);
    OPT(reference_string, n);
    LRU(reference_string, n);

    return 0;
}