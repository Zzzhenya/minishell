/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_and_run_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:46:22 by sde-silv          #+#    #+#             */
/*   Updated: 2024/05/09 17:53:46 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*

# define T_NULL 0
# define T_WORD 1
# define T_PIPE 2
# define T_REDIREC 3
# define T_S_QUOTE 4
# define T_D_QUOTE 5

*/

char	*get_heredoc_name(int count)
{
	char	*ret;
	char	*name;

	name = NULL;
	ret = NULL;
	ret = ft_itoa(count);
	name = ft_strjoin(HEREDOCNAME, ret);
	free (ret);
	return (name);
}

int	cleanup_heredocs(int count)
{
	char	*name;

	name = NULL;
	while (count > 0)
	{
		name = get_heredoc_name(count);
		unlink(name);
		count --;
		free (name);
	}
	return (1);
}

void	setup_temp(t_tmp *temp, char **arr, int *token)
{
	temp->arr = arr;
	temp->token = token;
	temp->name = NULL;
}

void	replace_word_by_name(t_tmp *temp, int i)
{
	free(temp->arr[i + 1]);
	temp->arr[i + 1] = ft_strdup(temp->name);
	free (temp->name);
	temp->name = NULL;
}

int	setup_and_run_heredoc(int *token, char **arr, t_envp *env)
{
	int		i;
	int		count;
	int		status;
	t_tmp	temp;

	i = 0;
	count = 1;
	status = 0;
	setup_temp(&temp, arr, token);
	while (arr[i])
	{
		if (*token == T_REDIREC && !ft_strncmp(arr[i], "<<", 3))
		{
			temp.name = get_heredoc_name(count);
			status = open_run_here(arr[i + 1], env, &temp);
			count ++;
			replace_word_by_name(&temp, i);
			if (status != 0)
				return (cleanup_heredocs(count));
		}
		i ++;
		token ++;
	}
	return (0);
}
