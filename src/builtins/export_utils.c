/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:59:46 by sde-silv          #+#    #+#             */
/*   Updated: 2024/04/02 17:59:49 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_export_error(char *var, char *val, char *message)
{
	ft_putstr_fd("bash: export: `", 2);
	if (var)
		ft_putstr_fd(var, 2);
	ft_putstr_fd(val, 2);
	ft_putchar_fd('\'', 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

int	is_valid_var_start(unsigned char c)
{
	if (ft_isalpha(c) || c == '_' || c == '=')
		return (1);
	else
		return (0);
}

int	is_valid_var_char(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '\0')
	{
		if (!(ft_isalnum((unsigned char)var[i]) || var[i] == '_' || var[i] == '='))
			return (0);
		i ++;
	}
	return (1);
}

void	print_variables_list(char **arr)
{
	int	i;

	i = 0;
	if (!arr || !arr[i])
		return ;
	while (arr[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(arr[i], STDOUT_FILENO);
		i ++;
	}
}

void	export_one_var(char **arr, t_envp *my_data)
{
	char	*var;
	char	*val;
	char	*str;
	char	*mid;

	/*if (arr[1] == NULL)
		val = ft_strdup("");*/
	//else
	val = arr[1];
	var = arr[0];
	mid = ft_strjoin(var, "=");
	str = ft_strjoin(mid, val);
	/*if (arr[1] == NULL)
		free(val);*/
	free (mid);
	unset_one_var(var, my_data);
	ft_lstadd_back(&my_data->envlist, ft_lstnew(str));
	my_data->count++;
}
