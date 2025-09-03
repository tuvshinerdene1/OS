#include <stdio.h>
#include <string.h>
int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Invalid number of arguments\n");
        return -1;
    }

    rename(argv[1], argv[2]);
    return 0;
}