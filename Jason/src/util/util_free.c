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
/*	[F]
	2d-array free
*/
void	free_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}

/*	[F]
	Free all elements of tree under the current node.
	It's recursive function.
	Free & free again until there is no node, should be freed.
	
	[Description]
	list of malloc in tree struct, should be free.
		1. t_cmd *l_child
		2. t_cmd *r_child
		3. chat **cmdstr	// value
		4. t_cmd *tree		// node itself.

	[Progress]
	1. tree == NULL // no need to free, already NULL.
	2. free_tree(tree->left_child)	// Recursive func: go into left tree.
	3. free_tree(tree->right_child)	// Recursive func: go into right tree.
	4. free_2d(tree->cmdstr)	// free 2times.
	5. free(tree)			// After free all inside things,
					// free pointer to structure(t_cmd *tree)
*/
void	free_tree(t_cmd	*tree)
{
	if (tree == NULL)
		return ;
	else
	{
		if (tree->left_child != NULL)
			free_tree(tree->left_child);
		if (tree->right_child != NULL)
			free_tree(tree->right_child);
		if (tree->cmdstr)
			free_2d(tree->cmdstr);
		free(tree);
	}
}

/*	[ ]	// Shenya

*/
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
