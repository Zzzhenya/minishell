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
	/* memo */
	printf(P"    [5] syntax_simple_redirect\n"RS);
	/* memo */

	*node = create_tree_node(N_SIMPLE_REDIREC, -1);

	/* memo */
	printf(B"    NODE TYPE:"RS" N_SIMPLE_REDIREC\n\n");
	printf(G"\t5. Go to the 'END'node: (left)N_RED_TYPE\n\n"RS);
	/* memo */

	(*node)->l_child
		= create_leaf_node(cmd_line, N_REDIREC_TYPE, i[0], i[0] + 1);

	/* memo */
	printf(RED"\n\t\t5-1. (left)N_RED_TYPE: %s\n\n"RS, *((*node)->l_child->cmdstr));
	printf(G"\t5. Go to the 'END'node: (right)N_FILE_NAME\n\n"RS);
	/* memo */

	(*node)->r_child
		= create_leaf_node(cmd_line, N_FILE_NAME, i[0] + 1, i[1]);
	
	/* memo */
	printf(RED"\n\t\t5-2. (right)N_FILE_NAME: %s\n\n"RS, *((*node)->r_child->cmdstr));
	/* memo */
	return (1);
}

int	syntax_redirects(char **cmd_line, int *token, int *i, t_cmd **node)
{
	int	tmp;
	int	next_redirec_index;

	/* memo */
	printf(P"    [4] syntax_redirects\n"RS);
	/* memo */

	tmp = i[1];
	*node = create_tree_node(N_REDIREC, -1);

	/* memo */
	printf(B"    NODE TYPE:"RS" N_REDIREC\n\n");
	printf("\t4. prev: i[1], cpy to the 'tmp': %d\n\n", i[1]);
	/* memo */

	next_redirec_index = find_index_next_redirec(token, i);
	if (next_redirec_index != -1)
		i[1] = next_redirec_index;

	/* memo */
	if (next_redirec_index != -1)
	{
		printf("\t\t4. We found the redirection more in string!!\n");
		printf("\t\t4. next redirection index i[1]: %d\n", i[1]);
		printf("\t\t4. cmd_line[i[1]]: %s\n\n", cmd_line[i[1]]);
	}
	if (next_redirec_index == -1)
	{
		printf(RED"\t\t5-3. No redirection is in token: (right)NULL\n"RS);
		printf("\n");
	}
	printf(G"\t4. Go to the [5]: (left)systax_simple_redirect\n\n"RS);
	/* memo */

	if (syntax_simple_redirect(cmd_line, i, &((*node)->l_child)) == -1)
		return (-1);
	if (next_redirec_index != -1)
	{	
		i[0] = next_redirec_index;
		i[1] = tmp;

		/* memo */
		printf("\t4-1. redirection index 0: %d\n", i[0]);
		printf("\t4-1. redirection index 1: %d\n", i[1]);
		printf(G"\t4-1. Go to the [5]: (right)systax_redirects\n\n"RS);
		/* memo */

		return (syntax_redirects(cmd_line, token, i, &((*node)->r_child)));
	}
	return (1);
}

int	syntax_simple_cmd(char **cmd_line, int *token, int *i, t_cmd **node)
{
	int		pipe_search_range[2];
	int		pipe_index;

	/* memo */
	printf(P"    [3] syntax_simple_cmd\n"RS);
	/* memo */

	pipe_search_range[0] = i[1];
	pipe_search_range[1] = check_token_length(token);
	pipe_index = find_index_pipe(token, pipe_search_range);
	*node = create_tree_node(N_SIMPLE_CMD, pipe_index);

	/* memo */
	printf(B"    NODE TYPE:"RS" N_SIMPLE_CMD\n\n");
	if (pipe_index == -1)
		printf("\t3. There is no more 'PIPE'\n\n");
	printf(G"\t3. Go to the 'END'node: (left)N_FILE_PATH\n\n"RS);
	/* memo */

	(*node)->l_child = create_leaf_node(cmd_line, N_FILE_PATH, i[0], i[0] + 1);

	/* memo */
	printf(RED"\n\t\t3-1. (left) N_FILE_PAHT: %s\n\n"RS, *((*node)->l_child->cmdstr));
	printf(G"\t3. Go to the 'END'node: (Right)N_ARGV\n\n"RS);
	/* memo */

	(*node)->r_child = create_leaf_node(cmd_line, N_ARGV, i[0], i[1]);
	
	/* memo */
	printf(RED"\n\t\t3-2. (right) N_ARGV: %s\n\n"RS, *((*node)->r_child->cmdstr));
	/* memo */
	return (1);
}

int	syntax_cmds(char **cmd_line, int *token, int *i, t_cmd **node)
{
	int	tmp;
	int	redirec_index;

	/* memo */
	printf(P"    [2] syntax_cmds\n"RS);
	/* memo */

	tmp = i[1];
	*node = create_tree_node(N_CMD, -1);

	/* memo */
	printf(B"    NODE TYPE:"RS" N_CMD\n\n");
	printf("\t2. prev: i[1], cpy to 'tmp': %d\n\n", i[1]);
	printf(G"\t2. Go to the [3]: (right)syntax_simple_cmd\n\n"RS);
	/* memo */

	redirec_index = find_index_redirec(token, i);
	if (redirec_index != -1)
		i[1] = redirec_index;
	
	/* memo */
	if (redirec_index != -1)
	{
		printf("\t\t2. We found the redirection in string!!\n");
		printf("\t\t2. curr: i[1] == %d\n", i[1]);
		printf("\t\t2. cmd_line[i[1]]: %s\n\n", cmd_line[i[1]]);
	}
	/* memo */

	if (syntax_simple_cmd(cmd_line, token, i, &((*node)->r_child)) != 1)
		return (-1);
	if (redirec_index != -1)
	{
		i[0] = redirec_index;
		i[1] = tmp;

		/* memo */
		printf("\t2-1. Current i[0] == redirect_index: from %d\n", redirec_index);
		printf("\t2-1. Current i[1] == cpy from 'tmp': to %d\n", tmp);
		printf(G"\t2-1. Go to the [4]: (left)syntax_redirects\n\n"RS);
		/* memo */

		return (syntax_redirects(cmd_line, token, i, &((*node)->l_child)));
	}
	return (1);
}

int	syntax_pipe(char **cmd_line, int *token, int *i, t_cmd **node)
{
	int	tmp;
	int	pipe_index;

	/* memo */
	printf(P"    [0] Original tokens\n"RS);
	int j = 0;
	while (cmd_line[j] != NULL)
		j++;
	int k = 0;
	while (k < j)
	{
		printf("    cmd_line[%d]:"G"%s\n"RS, k, cmd_line[k]);
		k++;
	}
	printf(P"\n    [1] syntax_pipe\n"RS);
	/* memo */

	tmp = i[1];
	pipe_index = find_index_pipe(token, i);
	*node = create_tree_node(N_CMD, pipe_index);
	
	/* memo */
	printf(B"    NODE TYPE:"RS" N_CMD\n\n");
	if (pipe_index == -1)
		printf(RED"\t1. No pipe is in token: (right)NULL\n"RS);
	/* memo */

	if (pipe_index != -1)
	{
		/* memo */
		printf("\t1. We found the pipe more in the string!!\n");
		/* memo */
		i[1] = pipe_index;
		if (pipe_index == i[0])
		{
			syntax_pipe_error_print();
			return (-1);
		}
	}

	/* memo */
	printf(G"\t1-1. Go to the [2]: (left)systax_cmds\n\n"RS);
	/* memo */

	if (syntax_cmds(cmd_line, token, i, &((*node)->l_child)) == -1)
		return (-1);
	if (pipe_index != -1)
	{
		update_pipe_index(i, pipe_index, tmp);
		/* memo */
		printf(G"\t1-1. Go to the [2]: (right)systax_pipe\n"RS);
		/* memo */
		return (syntax_pipe(cmd_line, token, i, &((*node)->r_child)));
	}
	return (1);
}
