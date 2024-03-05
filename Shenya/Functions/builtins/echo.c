#include "../minishell.h"

void	exec_echo(char **argv)
{
    int i;
    int opt;
    
    i = 1;
    opt = 0;
    while (argv[i] != NULL)
    {
        if (i == 1 && !ft_strncmp(argv[i], "-n", ft_strlen(argv[i])))
            opt = 1;
        else
        {
            ft_putstr_fd(argv[1], 1);
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
*/