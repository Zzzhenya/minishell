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

char	*get_pwd(void)
{
	char	*path;

	path = NULL;
	path = getcwd(path, PATH_MAX);
	if (!path)
	{
		g_exit_status = EX_CMD_NOT_FOUND;
		return (NULL);
	}
	else
		return (path);
}

/* When executing pwd should I exit when an error occurs
 and/or when successfully executed?

 is 127 the correct exit code for when getcwd fails? 
 */

void	exec_pwd(void)
{
	char	*path;

	path = NULL;
	path = get_pwd();
	if (!path)
		return ;
	else
	{
		ft_putstr_fd(path, 1);
		ft_putchar_fd('\n', 1);
		free (path);
	}
	g_exit_status = EXIT_SUCCESS;
	return ;
}
