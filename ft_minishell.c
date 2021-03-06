#include "ft_minishell.h"


void        ft_options(char **input){
    char    **hold;
    int     i;
    char    *command;
    char    *temp;

    i = 0;
    temp = ft_tabTospace(*input);
    free(*input);
    command = ft_strtrim(temp);
    free(temp);
    if (ft_strcmp(command, "") == 0){
        free(command);
        return;
    }
    hold = ft_strsplit(command, ' ');
    (ft_strcmp("cd" , hold[0]) == 0 && i == 0) ? ft_cd(hold[1]) : i++;
    (ft_strcmp("echo", hold[0]) == 0 && i == 1) ? ft_echo(command) : i++;
    (ft_strcmp("setenv", hold[0]) == 0 && i == 2) ? ft_setenv(hold[1]) : i++;
    (ft_strcmp("unsetenv", hold[0]) == 0 && i == 3) ? ft_unsetenv(hold[1]) : i++;
    (ft_strlen(command) > 0 && i == 4) ? ft_execute_comand(hold, &command) : i++;
    ft_freearry(hold);
    free(command);
}

void        ft_nooptions(char **input){
    char    **av;
    int     i;
    char    *pwds;
    char    *command;

    i = 0;
    command = ft_strtrim(*input);
    free(*input);
    if (ft_strcmp(command,"") == 0){
        free(command);
        return;
    }
    pwds = ft_pwd();
    av = (char **)malloc(sizeof(char *) * 2);
    av[0] = command;
    av[1] = (char *)0;
    if (ft_strcmp("exit", command) == 0)
    {
        free(&av[0]);
        free(pwds);   
        free(command);
        if (store != 0)
            ft_freearry(store);
        exit(1);
    }
    (ft_strcmp("pwd", command) == 0 && i == 0) ? ft_putendl(pwds): i++;
    free(pwds);
    (ft_strcmp("env", command) == 0 && i == 1) ? ft_envir(): i++;
    (ft_strcmp("cd", command) == 0 && i == 2) ? ft_cd("home"): i++;
    (ft_strlen(command) > 0 && i == 3) ? ft_execute_comand(av, 0) : i++;
    free(av);
    
    free(command);
}

void        ft_process(void){
    char    *input;
    
    input = 0;
    signal(SIGINT, ft_sighandler);
    while(1){
        ft_putstr("&> ");
        get_next_line(0, &input);
        (ft_elementcount(input, ' ') > 1) ? ft_options(&input) : ft_nooptions(&input);
    }
}

int main(void) {
    ft_process();
    return 0;
}
