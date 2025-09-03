#include <dirent.h>
#include <stdio.h>
#include <string.h>

long int findSize(char file_name[])
{
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        printf("File not found \n");
        return -1;
    }
    fseek(fp, 0L, SEEK_END);
    long int res = ftell(fp);
    fclose(fp);
    return res;
}

int main(void)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
        int count = 0;
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_name)
                if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, ".."))
                {
                    continue;
                }
            int size = findSize(dir->d_name);
            if (size >= 0)
            {
                printf("%d %s %d\n", count, dir->d_name, size);
            }
            else
            {
                printf("%d %s \n", count, dir->d_name);
            }

            count++;
        }
        printf("\n");
        closedir(d);
    }
    return 0;
}