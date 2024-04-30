/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:11:48 by tkwak             #+#    #+#             */
/*   Updated: 2024/03/13 11:24:07 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

int	syntax_simple_redirect(char **cmd_line, int *i, t_cmd **node)
{
	*node = create_tree_node(N_SIMPLE_REDIREC, -1);
	(*node)->l_child
		= create_leaf_node(cmd_line, N_REDIREC_TYPE, i[0], i[0] + 1);
	(*node)->r_child
		= create_leaf_node(cmd_line, N_FILE_NAME, i[0] + 1, i[1]);
	return (1);
}

int	syntax_redirects(char **cmd_line, int *token, int *i, t_cmd **node)
{
	int	tmp;
	int	next_redirec_index;

	tmp = i[1];
	*node = create_tree_node(N_REDIREC, -1);
	next_redirec_index = find_index_next_redirec(token, i);
	if (next_redirec_index != -1)
		i[1] = next_redirec_index;
	if (syntax_simple_redirect(cmd_line, i, &((*node)->l_child)) == -1)
		return (-1);
	if (next_redirec_index != -1)
	{	
		i[0] = next_redirec_index;
		i[1] = tmp;
		return (syntax_redirects(cmd_line, token, i, &((*node)->r_child)));
	}
	return (1);
}

int	syntax_simple_cmd(char **cmd_line, int *token, int *i, t_cmd **node)
{
	int		pipe_search_range[2];
	int		pipe_index;

	pipe_search_range[0] = i[1];
	pipe_search_range[1] = check_token_length(token);
	pipe_index = find_index_pipe(token, pipe_search_range);
	*node = create_tree_node(N_SIMPLE_CMD, pipe_index);
	(*node)->l_child = create_leaf_node(cmd_line, N_FILE_PATH, i[0], i[0] + 1);
	(*node)->r_child = create_leaf_node(cmd_line, N_ARGV, i[0], i[1]);
	return (1);
}

int	syntax_cmds(char **cmd_line, int *token, int *i, t_cmd **node)
{
	int	tmp;
	int	redirec_index;

	tmp = i[1];
	*node = create_tree_node(N_CMD, -1);
	redirec_index = find_index_redirec(token, i);
	if (redirec_index != -1)
		i[1] = redirec_index;
	if (syntax_simple_cmd(cmd_line, token, i, &((*node)->r_child)) != 1)
		return (-1);
	if (redirec_index != -1)
	{
		i[0] = redirec_index;
		i[1] = tmp;
		return (syntax_redirects(cmd_line, token, i, &((*node)->l_child)));
	}
	return (1);
}

int	syntax_pipe(char **cmd_line, int *token, int *i, t_cmd **node)
{
	int	tmp;
	int	pipe_index;

	tmp = i[1];
	pipe_index = find_index_pipe(token, i);
	*node = create_tree_node(N_CMD, pipe_index);
	if (pipe_index != -1)
	{
		i[1] = pipe_index;
		if (pipe_index == i[0])
		{
			syntax_pipe_error_print();
			return (-1);
		}
	}
	if (syntax_cmds(cmd_line, token, i, &((*node)->l_child)) == -1)
		return (-1);
	if (pipe_index != -1)
	{
		update_pipe_index(i, pipe_index, tmp);
		return (syntax_pipe(cmd_line, token, i, &((*node)->r_child)));
	}
	return (1);
}
