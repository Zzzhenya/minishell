/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:13:07 by tkwak             #+#    #+#             */
/*   Updated: 2024/03/13 10:13:14 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	free_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}

void	free_tree(t_cmd	*tree)
{
	if (tree == NULL)
		return ;
	else
	{
		if (tree->l_child != NULL)
			free_tree(tree->l_child);
		if (tree->r_child != NULL)
			free_tree(tree->r_child);
		if (tree->cmdstr)
			free_2d(tree->cmdstr);
		free(tree);
	}
}

void	free_stdios(t_stdio *stdios)
{
	t_stdio	*curr;
	t_stdio	*next;

	curr = stdios;
	while (curr)
	{
		next = curr->next_stdio;
		free(curr);
		curr = next;
	}
}

/* 
	frees a heap array upto a specified location
*/
void	free_arr(char **arr, int loc)
{
	int i;

	i = 0;
	while (i < loc)
	{
		free (arr[i]);
		arr[i] = NULL;
		i ++;
	}
	free (arr);
	arr = NULL;
}