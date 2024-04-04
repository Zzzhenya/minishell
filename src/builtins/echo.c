/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:23:56 by sde-silv          #+#    #+#             */
/*   Updated: 2024/04/03 15:24:01 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	if (argv[i][0] == '$' && argv[i][1] == '?')
		ft_putnbr_fd(g_exit_status, 1);
	else if (argv[i][0] == '$' && argv[i][1] == '$')
		ft_putnbr_fd(getpid(), 1);
	else
*/
void	exec_echo(char **argv)
{
	int	i;
	int	opt;
	int		count;
	char	**arr;

	count = 0;
	arr = NULL;
	count = count_non_empty_strings(&argv[1]);
	arr = strip_empty_strings(&argv[1]);
	i = 0;
	opt = 0;
	if (count > 0 && !ft_strncmp(arr[i], "-n", 3))
	{
		opt = 1;
		i ++;
	}
	while (i < count)
	{
		ft_putstr_fd(arr[i], 1);
		ft_putchar_fd(' ', 1);
		i ++;
	}
	if (opt == 0)
		ft_putchar_fd('\n', 1);
	if (arr)
		free_arr(arr, count);
	g_exit_status = 0;
}

/* 
manage env variables like $HOME - Expanded in parsing so its an array of strings
manage exceptions line $? $$ - Here 

It is assumed the $? is a seperate string in the char ** array ( for now)
*/
