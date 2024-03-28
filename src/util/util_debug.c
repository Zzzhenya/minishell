#include "../../include/minishell.h"

void	print_node(t_cmd *node)
{
	int i;

	i = 0;
	printf("%d 	", node->pre_flag);
	printf("%d 	", node->pipe_exist);
	if (!node->cmdstr)
	{
		printf ("Empty\n");
		return ;
	}
	while (node->cmdstr[i])
	{
		printf ("%s 	", node->cmdstr[i]);
		i ++;
	}
	printf ("\n");
}

/*

	Pre-order DFS Tree traversal
	if node is null ; return
	if the node has left child search left child tree
	if the node has right child or if the node type is N_CMD
		;search right child tree
	If node has no children print the node and return;

*/

void	print_tree(t_cmd *node)
{
	if (!node)
		return;
	if (node->l_child )
	{
		if (node->pre_flag == 0)
			print_node(node);
		node->pre_flag = 1;
		print_tree(node->l_child);
	}
	if (node->r_child || node->node_type == N_CMD)
	{
		if (node->pre_flag == 0)
			print_node(node);
		node->pre_flag = 1;
		print_tree(node->r_child);
	}
	if (!node->l_child && !node->r_child)
	{
		node->pre_flag = 1;
		print_node(node);
		return ;
	}
}