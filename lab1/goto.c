#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Invalid number of arguments\n");
        return -1;
    }

    int ret = chdir(argv[1]);
    if (ret)
    {
        fprintf(stderr, "error: %s\n", strerror(errno));
    }
    int returnCode = system("list");
    if (returnCode == 0)
    {
        printf("\Run List command successfully\n");
    }
    return 0;
}