#include "../minishell.h"

void	exec_echo(char **argv)
{
    int i;
    int opt;
    
    i = 1;
    opt = 0;
    if (argv[i] != NULL && i == 1 && !ft_strncmp(argv[i], "-n", 3))
    {
        opt = 1;
        i ++;
    }
    while (argv[i] != NULL)
    {
        if (argv[i][0] == '$' && argv[i][1] == '?')
            ft_putnbr_fd(g_exit_status, 1);
        else if (argv[i][0] == '$' && argv[i][1] == '$')
            ft_putnbr_fd(getpid(), 1);
        else
        {
            ft_putstr_fd(argv[i], 1);
            ft_putchar_fd(' ', 1);
        }
        i ++;
    }
    if (opt == 0)
        ft_putchar_fd('\n', 1);
    g_exit_status = 0;
}

/* 
manage env variables like $HOME - Expanded in parsing so its an array of strings
manage exceptions line $? $$ - Here 

It is assumed the $? is a seperate string in the char ** array ( for now)
*/