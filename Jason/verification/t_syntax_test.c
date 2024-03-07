#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

# define N_CMD 1
# define N_SIMPLE_CMD 2
# define N_FILE_PATH 3
# define N_ARGV 4
# define N_REDIREC 5
# define N_SIMPLE_REDIREC 6
# define N_REDIREC_TYPE 7
# define N_FILE_NAME 8

# define T_NULL 0
# define T_WORD 1
# define T_PIPE 2
# define T_REDIREC 3
# define T_S_QUOTE 4
# define T_D_QUOTE 5

typedef struct s_cmd
{
	struct s_cmd		*l_child;
	struct s_cmd		*r_child;
	char				**cmdstr;
	int					node_type;
	int					pipe_exist;
	int					pre_flag;
}	t_cmd;

int	find_target_index(int *token, int target, int *i)
{
	int	index;

	index = i[0];
	while (index < i[1])
	{
		if (token[index] == target)
			return (index);
		index++;
	}
	return (-1);
}

int	find_index_pipe(int *token, int *i)
{
	return (find_existence(token, T_PIPE, i));
}

int	find_index_redirec(int *token, int *i)
{
	return (find_existence(token, T_REDIREC, i));
}

int	find_index_next_redirec(int *token, int *i)
{
	int	index[2];

	index[0] = i[0] + 1;
	index[1] = i[1];
	return (find_existence(token, T_REDIREC, index));
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

t_cmd	*create_tree_node(int type, int pipe_index)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	new_node->node_type = type;
	new_node->l_child = NULL;
	new_node->r_child = NULL;
	new_node->cmdstr = NULL;
	new_node->pipe_exist = pipe_index;
	return (new_node);
}

t_cmd	*create_leaf_node(char **cmd_line, int type, int start, int end)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	new_node->node_type = type;
	new_node->l_child = NULL;
	new_node->r_child = NULL;
	new_node->cmdstr = copy_substring_range(cmd_line, start, end);
	new_node->pipe_exist = -1;
	return (new_node);
}

int	syntax_simple_cmd(char **cmd_line, int *token, int *i, t_cmd **node)
{
	int		pipe_check[2];
	int		pipe_index;

	pipe_check[0] = i[1];
	pipe_check[1] = token_length(token);
	pipe_index = find_index_pipe(token, pipe_check);
	*node = generate_new_tree(N_SIMPLE_CMD, pipe_index);
	(*node)->l_child = generate_end_tree(cmd_line, N_FILE_PATH,
			i[0], i[0] + 1);
	(*node)->r_child = generate_end_tree(cmd_line, N_ARGV, i[0], i[1]);
	return (1);
}

int	syntax_cmds(char **input_cmdline, int *token, int *i, t_cmd **node)
{
	int	redirec_index;
	int	tmp;

	tmp = i[1];
	*node = generate_tree(N_CMD, -1);
	redirec_index = find_index_redirec(token, i);
	if (redirec_index == -1)
	{
		if (syntax_simple_cmd(input_cmdline, token, i, &((*node)->r_child)) != 1)
			return (-1);
	}
	else
	{
		i[1] = redirec_index;
		if (syntax_simple_cmd(input_cmdline, token, i, &((*node)->r_child)) != 1)
			return (-1);
		i[0] = redirec_index;
		i[1] = tmp;
		return (syntax_redirects(input_cmdline, token, i, &((*node)->l_child)));
	}
	return (1);
}

void	update_pipe_index(int *i, int pipe_index, int tmp)
{
	i[0] = pipe_index + 1;
	i[1] = tmp;
}

int	syntax_pipe(char **cmd_line, int *token, int *i, t_cmd **node)
{
	int		pipe_index;
	int		tmp;

	tmp = i[1];
	pipe_index = find_index_pipe(token, i);
	*node = generate_new_tree(N_CMD, pipe_index);
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
