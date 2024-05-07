/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:50:12 by sde-silv          #+#    #+#             */
/*   Updated: 2024/05/07 18:50:14 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	not_a_dir(char	*path)
{
	struct stat	statbuf;

	statbuf.st_mode = 0;
	stat(path, &statbuf);
	if (S_ISREG(statbuf.st_mode))
		return (1);
	else
		return (0);
}

void	print_cd_error(char *path, char *message)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(message, 2);
}
