#include <stdio.h>
int main(int argc, char **argv)
{
    FILE *f = NULL;
    for (int i = 1; i < argc; i++)
    {
        f = fopen(argv[i], "w");
    }
    return 0;
}