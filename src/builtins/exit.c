/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:38:31 by sde-silv          #+#    #+#             */
/*   Updated: 2024/04/10 13:35:55 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_stuff_and_exit(t_envp *my_data, int yes)
{
	if ((my_data->builtin == 1 && my_data->cmds == 1) || yes == 1)
	{
		clear_envlist(my_data);
		if (my_data->cd_hist != NULL)
		{
			free (my_data->cd_hist);
			my_data->cd_hist = NULL;
		}
		if (my_data->envarr)
			free_arr(my_data->envarr, my_data->count);
		if (my_data->paths)
			free_2d(my_data->paths);
		if (my_data->tree)
			free_tree(my_data->tree);
		if (my_data->user_input)
		{
			free(my_data->user_input);
			my_data->user_input = NULL;
		}
		rl_clear_history();
	}
	exit (g_exit_status);
}

int	ft_isanumber(char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
	{
		sign ++;
		i ++;
	}
	while (str[i] != '\0' && ft_isdigit(str[i]))
		i ++;
	if (str[i] != '\0' && !ft_isdigit(str[i]))
		return (0);
	else
		return (i - sign);
}

void	print_exit_error(char *string, char *message)
{
	ft_putstr_fd("bash: exit: ", 2);
	if (string)
		ft_putstr_fd(string, 2);
	ft_putstr_fd(message, 2);
}

static void	handle_exit_codes(char **arr, int digcount,
		int count, t_envp *my_data)
{
	if (digcount > 0 && digcount <= 19 && count < 2)
	{
		if (ft_atoi(arr[0]) >= 0 && ft_atoi(arr[0]) <= 255)
			g_exit_status = ft_atoi(arr[0]);
		else if (ft_atoi(arr[0]) < 0)
			g_exit_status = 256 + ft_atoi(arr[0]);
		else
			g_exit_status = ft_atoi(arr[0]) - 256;
		free_stuff_and_exit(my_data, 0);
	}
	else if (digcount > 0 && count >= 2)
	{
		print_exit_error(NULL, "too many arguments\n");
		g_exit_status = 1;
		return ;
	}
}

/* Need to free stuff before exit */
void	exec_exit(char **argv, t_envp *my_data)
{
	int		digcount;
	char	**arr;
	int		count;

	digcount = 0;
	if (my_data->builtin == 1 && my_data->cmds == 1)
		ft_putstr_fd("exit\n", 2);
	arr = NULL;
	arr = strip_empty_strings(&argv[1]);
	count = count_non_empty_strings(&argv[1]);
	if (count == 0)
		free_stuff_and_exit(my_data, 0);
	digcount = ft_isanumber(arr[0]);
	if (digcount != 0)
		handle_exit_codes(arr, digcount, count, my_data);
	else
	{
		print_exit_error(arr[0], ": numeric argument required\n");
		g_exit_status = 2;
		free_stuff_and_exit(my_data, 0);
	}
}
