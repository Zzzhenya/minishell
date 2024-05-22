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
		return (i * sign);
}

void	print_exit_error(char *string, char *message)
{
	ft_putstr_fd("bash: exit: ", 2);
	if (string)
		ft_putstr_fd(string, 2);
	ft_putstr_fd(message, 2);
}

static int	handle_exit_codes(char **arr, int digcount,
		int count)
{
	int	ret;

	ret = 0;
	if (digcount > 0 && digcount <= 19 && count < 2)
	{
		if (ft_atoi(arr[0]) >= 0 && ft_atoi(arr[0]) <= 255)
			ret = ft_atoi(arr[0]);
		else if (ft_atoi(arr[0]) < 0)
			ret = 256 + ft_atoi(arr[0]);
		else
			ret = ft_atoi(arr[0]) - 256;
		return (ret);
	}
	else if (digcount > 0 && count >= 2)
	{
		print_exit_error(NULL, "too many arguments\n");
		g_exit_status = 1;
		return (0);
	}
	else
		return (0);
}

void	set_value_free(t_envp *my_data, int c, int ret)
{
	my_data->arr[c].status = ret;
	free_stuff_and_exit(my_data, 1, c);
}

/* Need to free stuff before exit\
	free_stuff_and_exit()last variable should be the cmd index of exec exit
*/
void	exec_exit(char **argv, t_envp *my_data, int c)
{
	int		digcount;
	char	**arr;
	int		count;
	int		ret;

	digcount = 0;
	ret = 0;
	if (my_data->builtin == 1 && my_data->procs == 1)
		ft_putstr_fd("exit\n", 2);
	arr = &argv[1];
	count = get_arg_count(&argv[1]);
	if (count == 0)
		free_stuff_and_exit(my_data, 1, c);
	digcount = ft_isanumber(arr[0]);
	if (digcount != 0)
	{
		ret = handle_exit_codes(arr, digcount, count);
		if (ret != 0)
			set_value_free(my_data, c, ret);
	}
	else
	{
		print_exit_error(arr[0], ": numeric argument required\n");
		set_value_free(my_data, c, 2);
	}
}
