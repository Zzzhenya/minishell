/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_change_exit_status.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:48:21 by tkwak             #+#    #+#             */
/*   Updated: 2024/03/13 17:48:51 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	if_dollar_q_mark(char **tmp, char *status, int *flag, int *i)
{
	if (ft_strcmp(status, "13") == 0)
		*tmp = strrjoin(*tmp, "0");
	else
		*tmp = strrjoin(*tmp, status);
	*flag = 1;
	*i += 2;
}

void	if_tmp(int *flag, char *tmp, char **argv)
{
	if (*flag == 1)
	{
		*flag = 0;
		free((*argv));
		(*argv) = ft_strdup(tmp);
	}
	return ;
}

char	*convert_status_to_ascii(void)
{
	char	*status;

	if (g_exit_status == 512)
		status = ft_itoa(2);
	else if (g_exit_status == 256)
		status = ft_itoa(1);
	else
		status = ft_itoa(g_exit_status);
	return (status);
}

void	replace_exit_status(char ***argv, int i, int flag, int j)
{
	char	*tmp;
	char	*status;

	status = convert_status_to_ascii();
	if ((*argv) == NULL || (**argv) == NULL)
		return ;
	while ((*argv)[i])
	{
		tmp = NULL;
		while ((*argv)[i][j] && ft_strchr_m((*argv)[i], '$') != -1
			&& ft_strchr_m((*argv)[i], '?') != -1)
		{
			if ((*argv)[i][j] && (*argv)[i][j] == '$'
			&& (*argv)[i][j + 1] == '?')
				if_dollar_q_mark(&tmp, status, &flag, &j);
			else if ((*argv)[i][j] == '\0')
				break ;
			else
				tmp = strjoin_c(tmp, (*argv)[i][j++]);
		}
		if_tmp(&flag, tmp, &(*argv)[i++]);
		j = 0;
	}
	free(status);
	return ;
}

void	free_together(char **av1, char *av2)
{
	free (av1);
	free (av2);
}
