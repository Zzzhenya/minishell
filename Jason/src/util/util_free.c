void	free_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i ++]);
	free(arr);
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

/* [ ]
//
*/
void	freeing_norminette(char **validated_input, int *token)
{
	free_2d(validated_input);
	free(token);
}
