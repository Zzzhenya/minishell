/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_create_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:11:56 by tkwak             #+#    #+#             */
/*   Updated: 2024/03/13 11:11:58 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

t_cmd	*create_tree_node(int type, int pipe_index)
{
	t_cmd	*new_node;

	// /* memo */
	// printf(B"    !!Tree_node_created!!\n"RS);
	// /* memo */
	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	new_node->node_type = type;
	new_node->l_child = NULL;
	new_node->r_child = NULL;
	new_node->cmdstr = NULL;
	new_node->pipe_exist = pipe_index;
	return (new_node);
}

char	**copy_substring_range(char **cmd_line, int start, int end)
{
	int		i;
	char	**res;

	res = (char **)malloc((sizeof(char *)) * (end - start + 1));
	if (!res)
		exit(errno);
	i = 0;
	while (i < end - start)
	{
		res[i] = ft_strdup(cmd_line[start + i]);
		if (!res[i])
			exit(errno);
		i++;
	}
	res[i] = NULL;
	return (res);
}

t_cmd	*create_leaf_node(char **cmd_line, int type, int start, int end)
{
	t_cmd	*new_node;

	// /* memo */
	// printf(B"\t   !!End_node_created!!\n"RS);
	// /* memo */
	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	new_node->node_type = type;
	new_node->l_child = NULL;
	new_node->r_child = NULL;
	new_node->cmdstr = copy_substring_range(cmd_line, start, end);
	// /* memo */
	// if (new_node->cmdstr != NULL)
	// {
	// 	printf("\t   Finished to cpy user_input to the 'cmdstr'\n");
	// 	printf("\t   Current cmdstr: %s\n", new_node->cmdstr[0]);
	// }
	// /* memo */
	new_node->pipe_exist = -1;
	return (new_node);
}
