#include <stdio.h>
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Invalid number of arguments\n");
        return -1;
    }

    if (remove(argv[1]) == 0)
    {
        printf("File has been deleted successfully.\n");
    }
    else
    {
        printf("Error occured while trying to delete the file\n");
    }
    return 0;
}