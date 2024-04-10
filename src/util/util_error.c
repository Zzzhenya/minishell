/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:13:21 by tkwak             #+#    #+#             */
/*   Updated: 2024/03/13 10:13:22 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	syntax_pipe_error_print(void)
{
	write(2, "syntax error near unexpected token '|'\n",
		ft_strlen("syntax error near unexpected token '|'\n"));
	g_exit_status = 1;
}

int	find_matching_env_row(char *str, char **env)
{
	int	i;

	i = 0;
	if (str == NULL && *str == '\0')
		return (-1);
	while (env[i] != NULL)
	{
		if (!ft_strncmp(env[i], str, ft_strlen(str)))
			return (i);
		i++;
	}
	return (-1);
}
