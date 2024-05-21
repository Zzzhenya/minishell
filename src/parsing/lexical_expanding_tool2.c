/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_expanding_tool2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:12:50 by tkwak             #+#    #+#             */
/*   Updated: 2024/05/17 11:10:14 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_pid_string(void)
{
	pid_t	pid;

	pid = getpid();
	return (ft_itoa((int)pid));
}

void	skip_non_dollar(t_expand *data, char **array_split)
{
	while (array_split[data->x][data->y]
			&& array_split[data->x][data->y] != '$')
	{
		data->res1[data->y] = array_split[data->x][data->y];
		data->y++;
	}
	data->res1[data->y] = '\0';
	data->y++;
}

void	skip_non_space_sq(t_expand *data,
		char **array_split, char **env, int *i)
{
	while (array_split[data->x][data->y] != ' '
			&& array_split[data->x][data->y] != '\'')
	{
		data->res[data->z] = array_split[data->x][data->y];
		data->y++;
		data->z++;
	}
	data->res[data->z] = '\0';
	data->row_env = find_matching_env_row(&data->res[data->x], env);
	if (data->row_env == -1)
	{
		array_split[*i]
			= replace_substring_1(array_split[*i], "", data->i_dollar);
	}
	else
	{
		data->tmp = replace_substring_special(data, env, 0);
		data->tmp = ft_strjoin(data->res1, data->tmp);
		free(data->res1);
	}
}
