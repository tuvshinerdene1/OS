#include <stdio.h>
int main(int argc, char **argv)
{
    FILE *f = NULL;

    if (argc != 3)
    {
        printf("Invalid amount of arguments.\n");
        return -1;
    }

    f = fopen(argv[1], "a");
    if (f == NULL)
    {
        printf("The file is not opened\n");
        return -1;
    }
    else
    {
        fputs("\n", f);
        fputs(argv[2], f);
        fclose(f);
    }

    return 0;
}