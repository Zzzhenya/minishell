/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:38:31 by sde-silv          #+#    #+#             */
/*   Updated: 2024/04/02 20:38:32 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static void	handle_exit_codes(char **arr, int digcount, int count)
{
	if (digcount > 0 && digcount <= 19 && count < 2)
	{
		if (ft_atoi(arr[0]) >= 0 && ft_atoi(arr[0]) <= 255)
			g_exit_status = ft_atoi(arr[0]);
		else if (ft_atoi(arr[0]) < 0)
			g_exit_status = 256 + ft_atoi(arr[0]);
		else
			g_exit_status = ft_atoi(arr[0]) - 256;
		exit (g_exit_status);
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
	int	digcount;
	char **arr;
	int count;

	//(void)my_data;
	digcount = 0;
	if (my_data->builtin == 1 && my_data->cmds == 1)
		ft_putstr_fd("exit\n", 2);
	arr = NULL;
	arr = strip_empty_strings(&argv[1]);
	count = count_non_empty_strings(&argv[1]);
	if (count == 0)
		exit (g_exit_status);
	digcount = ft_isanumber(arr[0]);
	// if first argument is a number
	if (digcount != 0)
		handle_exit_codes(arr, digcount, count);
	else
	{
		print_exit_error(arr[0], ": numeric argument required\n");
		g_exit_status = 2;
		exit(g_exit_status);		
	}
	/*
	if (!argv[1])
	{
		exit(g_exit_status);
	}
	digcount = ft_isanumber(argv[1]);
	if (digcount)
		handle_exit_codes(argv, digcount);
	else
	{
		print_exit_error(argv[1], ": numeric argument required\n");
		g_exit_status = 2;
		exit(g_exit_status);
	}*/
}
