/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:23:56 by sde-silv          #+#    #+#             */
/*   Updated: 2024/04/04 14:58:25 by sde-silv         ###   ########.fr       */
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

static int is_a_minus_n_combo(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] && str[i] == '-')
		i ++;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i ++;
	}
	return (1);
}

void	exec_echo(char **argv, int c, char **arr, t_envp *my_data)
{
	int	i;
	int count = 0;
	int	opt;
	char *path = NULL;

	// count = count_non_empty_strings(&argv[1]);
	// arr = strip_empty_strings(&argv[1]);
	count = get_arg_count(&argv[1]);
	arr = &argv[1];
	i = 0;
	opt = 0;
	if (count > 0 && !ft_strncmp(arr[i], "-n", 3))
	{
		opt = 1;
		while (is_a_minus_n_combo(arr[i]))
			i ++;
	}
	while (i < count)
	{
		if (!ft_strcmp(arr[i], "~"))
		{
			path = change_to_home(my_data);
			ft_putstr_fd(path, 1);
			free (path);
		}
		else
			ft_putstr_fd(arr[i], 1);
		if (i + 1 < count)
			ft_putchar_fd(' ', 1);
		i ++;
	}
	if (opt == 0)
		ft_putchar_fd('\n', 1);
	// if (arr)
	// 	free_arr(arr, count);
	my_data->arr[c].status = 0;
}
