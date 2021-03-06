#include "ft_minishell.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>


void ft_execute_comand(char **av, char **command)
{
    char    *temp;
    char    *fullpath;

    temp = 0;                  
    fullpath = 0;                                
    if (fork() == 0){
            if ((ft_strstr(av[0], "/bin/") != 0 || ft_strstr(av[0], "/") != 0) && av){
                temp = ft_strjoin("minishell: no such file or directory: ", av[0]);
                execve(av[0], av, environ) < 1 ? ft_putendl(temp) : (void)0;
                free(temp);
            }else if(ft_envKeys("PATH=")){
                temp = ft_strjoin("minishell: command not found: ", av[0]);                                                     
                fullpath = ft_strjoin("/bin/", av[0]);                             
                execve(fullpath, av, environ) < 1 ? ft_putendl(temp) : (void)0;
                free(fullpath);
                if (av[1]){
                    free(*command);
                     ft_freearry(av);
                }
                else
                {
                    free(*av);
                    free(av);

                }
                free(temp);
                exit(0);
            }else{
                ft_putstr("minishell: no such file or directory: ");                                                          
                ft_putendl(av[0]);
                if (av[1]){
                    free(*command);
                     ft_freearry(av);
                }
                else{
                    free(*av);
                     free(av);
                }
                if (store != 0)
            ft_freearry(store);
            exit(0);
            }
        if (av[1])
                free(*command);
            else
                free(*av);
            free(av);
        if (store != 0)
            ft_freearry(store);
        exit(0);                                                                
    }                                                                           
    wait(0);  
}