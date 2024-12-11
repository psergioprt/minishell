#include "../../include/minishell.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    //char *argv[] = {"ls", "-l", NULL};  // Arguments for the `ls` command
    char *envp[] = {"PATH=/bin:/usr/bin", NULL};  // Environment variables
    if (argc)
        printf("sou lindo \n");
    // Replace the current process with the `ls -l` command
    if (execve(argv[1], argv, envp) == -1) {
        perror("execve failed");
        exit(EXIT_FAILURE);
    }

    return 0;  // This line is never reached unless execve fails
}

