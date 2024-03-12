#include "../minishell.h"

void	exec_env(char **argv, t_envp *my_data)
{
	/*
	int i = 0;
	(void)argv;
	while (my_data->envp[i] != NULL)
	{
		ft_putstr_fd(my_data->envp[i], 1);
		ft_putchar_fd('\n', 1);
		i ++;
	}*/
	t_list *lst;

	(void)argv;
	lst = (my_data->envlist);
	while (lst)
	{
		ft_putstr_fd((char *)lst->content, 1);
		ft_putchar_fd('\n', 1);
		lst = lst->next;
	}
}