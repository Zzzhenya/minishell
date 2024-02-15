#include <stdlib.h>
#include <stdio.h>

#define T_NULL 0
#define T_WORD 1
#define T_PIPE 2
#define T_REDIRECT 3
#define T_DOUBLE_QUOTES 4
#define T_SINGLE_QUOTES 5

typedef struct s_token 
{
	int	type;
	char	*str;
}	t_token;

typedef struct s_bst 
{
	void			*node;
	struct s_bst	*right;
	struct s_bst	*left;
}	t_bst;

/*
void	search_tree(t_ast *node)
{
	execute_tree(node);
	if (node->left != NULL)
		search_tree(node->left);
	if (node->right != NULL)
		search_tree(node->right);
}*/

int main (void)
{
	char *first = "ls";
	char *second = "-la";
	char *third = "|";
	char *fourth = ">";
	char *fifth = "a";
	t_token	*arr = NULL;

	arr = malloc (sizeof(t_token) * 5);
	arr[0].type = T_WORD;
	arr[0].str = first;
	arr[1].type = T_WORD;
	arr[1].str = second;
	arr[2].type = T_PIPE;
	arr[2].str = third;
	arr[3].type = T_REDIRECT;
	arr[3].str = fourth;
	arr[4].type = T_WORD;
	arr[4].str = fifth;

	int i = 0;
	while (i < 5)
	{
		printf("%s ", arr[i].str);
		i ++;
	}
	printf("\n");
	i = 0;
	while (i < 5)
	{
		printf("%d ", arr[i].type);
		i ++;
	}
	printf("\n");



	return (0);
}