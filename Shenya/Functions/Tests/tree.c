#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	printf("%d 	", node->pipe_exist);
	if (node->node_type == N_CMD)
		printf("%s 	", "N_CMD");
	else if (node->node_type == N_SIMPLE_CMD)
		printf("%s 	", "N_SIMPLE_CMD");
	else if (node->node_type == N_FILE_PATH)
		printf("%s 	", "N_sFILE_PATH");
	else if (node->node_type == N_ARGV)
		printf("%s 	", "N_ARGV");
	else if (node->node_type == N_REDIREC)
		printf("%s 	", "N_REDIREC");
	else if (node->node_type == N_SIMPLE_REDIREC)
		printf("%s 	", "N_SIMPLE_REDIREC");
	else if (node->node_type == N_REDIREC_TYPE)
		printf("%s 	", "N_REDIREC_TYPE");
	else
		printf("%s 	", "N_FILE_NAME");
	//printf("%d 	", node->node_type);*
*/

typedef struct s_cmd
{
	struct s_cmd		*l_child;
	struct s_cmd		*r_child;
	char 				*str;
//	char				**cmdstr;
//	int					node_type;
//	int					pipe_exist;
	int					pre_flag;
}	t_cmd;

void	print_node(t_cmd *node)
{
	int i = 0;

	printf("%d 	", node->pre_flag);
	if (!node->str)
	{
		printf("Empty\n");
		return ;
	}
	while (node->cmdstr[i])
	{
		printf("%s 	", node->cmdstr[i]);
		i ++;
	}
	printf("\n");
}

void	search_tree(t_cmd *node)
{
	//print_leaves(node, paths, env);
	if (!node)
		return;
	// If node has no children print the node and return;
	if (!node->l_child && !node->r_child)
	{
		node->pre_flag = 1;
		print_node(node);
		return ;
	}
	// if the node has left child search left child tree
	if (node->l_child )
	{
		if (node->pre_flag == 0)
			print_node(node);
		node->pre_flag = 1;
		search_tree(node->l_child);
	}
	// if the node has right child search right child tree
	if (node->r_child )
	{
		if (node->pre_flag == 0)
			print_node(node);
		node->pre_flag = 1;
		search_tree(node->r_child);
	}

}

t_cmd *add_node(t_cmd *node, char *str)
{
	if (!node)
		node = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	node->str = strdup(str);
	node->l_child = NULL;
	node->r_child = NULL;
	node->pre_flag = 0;
	return (node);
}

int main (void)
{
	t_cmd	*tree;

	tree = NULL;
	tree = add_node(tree, "pipe_type"); // |
	tree->l_child = add_node(tree->l_child, "redirec_type"); // >
	tree->l_child->l_child = add_node(tree->l_child->l_child, "Hello");
	tree->l_child->r_child = add_node(tree->l_child->r_child, "a");
	tree->r_child = add_node(tree->l_child, "pipe_type"); // |
	tree->r_child->l_child = add_node(tree->r_child->l_child, "cat -e");
	tree->r_child->r_child = add_node(tree->r_child->r_child, "redirec_type"); // append
	tree->r_child->r_child->l_child = add_node(tree->r_child->r_child->l_child, "env");
	tree->r_child->r_child->r_child = add_node(tree->r_child->r_child->r_child, " a");
	search_tree(tree);
	return (0);
}