/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_find_target.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:12:04 by tkwak             #+#    #+#             */
/*   Updated: 2024/03/13 11:12:06 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int	find_target_index(int *token, int target, int *i)
{
	int	index;

	index = i[0];
	while (index < i[1])
	{
		if (token[index] == target)
			return (index);
		index++;
	}
	return (-1);
}

int	find_index_pipe(int *token, int *i)
{
	return (find_target_index(token, T_PIPE, i));
}

int	find_index_redirec(int *token, int *i)
{
	return (find_target_index(token, T_REDIREC, i));
}

int	find_index_next_redirec(int *token, int *i)
{
	int	index[2];

	index[0] = i[0] + 1;
	index[1] = i[1];
	return (find_target_index(token, T_REDIREC, index));
}

void	update_pipe_index(int *i, int pipe_index, int tmp)
{
	i[0] = pipe_index + 1;
	i[1] = tmp;
}
