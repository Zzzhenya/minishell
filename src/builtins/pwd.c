/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:49:16 by sde-silv          #+#    #+#             */
/*   Updated: 2024/04/02 20:49:43 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_pwd(t_envp *my_data, int c)
{
	char	*path;

	path = NULL;
	path = getcwd(path, PATH_MAX);
	if (!path)
	{
		my_data->arr[c].status = 0;
		return (NULL);
	}
	else
		return (path);
}

/* When executing pwd should I exit when an error occurs
 and/or when successfully executed?

 is 127 the correct exit code for when getcwd fails? 
 */

void	exec_pwd(t_envp *my_data, int c)
{
	char	*path;

	path = NULL;
	path = get_pwd(my_data, c);
	if (!path)
	{
		ft_putstr_fd("getcwd: cannot access parent directories: No such file or directory", 1);
		ft_putchar_fd('\n', 1);
		return ;
	}
	else
	{
		ft_putstr_fd(path, 1);
		ft_putchar_fd('\n', 1);
		free (path);
	}
	my_data->arr[c].status = EXIT_SUCCESS;
	return ;
}
