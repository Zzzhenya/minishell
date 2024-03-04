#include "../minishell.h"

void	exec_env(char **argv, t_envp *my_data)
{
	int i = 0;
	(void)argv;
	while (my_data->envp[i] != NULL)
	{
		ft_putstr_fd(my_data->envp[i], 1);
		ft_putchar_fd('\n', 1);
		i ++;
	}
}