#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"

extern char **environ;

int ft_strarrlen(char **arr){
    int i;

    i = 0;
    while(arr[i] != 0)
        i++;
    return i;
}

char **realloc_environ(char **environ, char *s){
    int i;
    char **new_environ;

    i = 0;
    new_environ = (char **)malloc(sizeof(char *) * (ft_strarrlen(environ) + 1));
    new_environ[ft_strarrlen(environ) + 1] = 0;
    while(environ[i] != 0){
        new_environ[i] = environ[i];
        i++;
    }
    new_environ[i] = s;
    return new_environ;
}

int main(int ac, char **av)
{
    int i = 0;
    char **s;

    environ = realloc_environ(environ, "FOO=bar");
    execve(av[1], av, NULL);

    return 0;
}