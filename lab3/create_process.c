#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Invalid number of arguments\n");
        return -1;
    }
    pid_t pid;
    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0)
    {

        execlp(argv[1], argv[1], (char *)NULL);
        perror("execlp failed");
        exit(1);
    }
    else
    {
        wait(NULL);
        printf("Parent process finished waiting for child.\n");
    }

    return 0;
}
