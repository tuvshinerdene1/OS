#include <stdio.h>
#include <unistd.h>
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Invalid number of arguments\n");
        return -1;
    }
    chdir(argv[1]);
    return 0;
}