#include "../../include/minishell.h"

// Temporary declaration
extern int	g_exit_status;

# define N_NULL	0
# define N_PIPE 1
# define N_CMD 2			//
# define N_SIMPLE_CMD 3		//
# define N_FILE_PATH 4		
# define N_ARGV 5
# define N_REDIREC 6		//
# define N_SIMPLE_REDIREC 7	//
# define N_REDIREC_TYPE 8
# define N_FILE_NAME 9

typedef struct s_cmd
{
	struct s_cmd		*l_child;
	struct s_cmd		*r_child;
	char				**cmdstr;
	int					node_type;		// N_PIPE, N_CMD, N_SIMPLE_CMD, N_ARGV, N_FILE_NAME ...
	int					pipe_exist;		// Check whether it exist or not, when exist, return (position)
	int					pre_flag;
}	t_cmd;

# define T_NULL 0
# define T_WORD 1
# define T_PIPE 2
# define T_REDIREC 3
# define T_S_QUOTE 4
# define T_D_QUOTE 5
// Temporary declaration








/*	[F]	
	[Form & Param]
	find_index_pipe(token, T_PIPE(or T_REDIREC), i);
		Param(1): Array, saves the type of tokens // W P R S D
		Param(2): Target(= T_PIPE)
		Param(3): Pointer to integer from the function("parse_input_cmdline")
					i[0]: 0		// Starting
					i[1]: 5		// Length of token

	[Explanaion]
	Find the existence of the "pipe" or the "redirection" among the tokens.
	If found, returns an (INDEX) of position of it.
*/
int	find_existence(int *token, int target, int *i)
{
	int	count;

	count = i[0];
	while (count < i[1])
	{
		if (token[count] == target)
			return (count);
		count++;
	}
	return (-1);
}

/*	[F]	
	Target = T_PIPE
*/
int	find_index_pipe(int *token, int *i)
{
	return (find_existence(token, T_PIPE, i));
}

/*	[F]	
	[Form & Param]
	generate_tree(N_CMD, pipe_index);
					2	  position

	[Explanation]
	Generate the new tree node,
	1. Save the data about the "node_type" and "pipe's position".
	2. allocate memory as many as "t_cmd".
	3. Every tree has left, right child node.
*/
t_cmd	*generate_tree(int type, int pipe_index)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	new_node->l_child = NULL;
	new_node->r_child = NULL;
	new_node->cmdstr = NULL;
	new_node->node_type = type;
	new_node->pipe_exist = pipe_index;
	return (new_node);
}

/*	[F]
	Error handling for pipe function.
	
	In write function, first param means "fd".
		fd 0: stdin
		fd 1: stdout
		fd 2: stderr
*/
void	syntax_pipe_error_print(void)
{
	write(2, "syntax error near unexpected token '|'\n",
		ft_strlen("syntax error near unexpected token '|'\n"));
	g_exit_status = 1;
}

/*	[F]	
	Target = T_REDIREC
*/
int	find_index_redirec(int *token, int *i)
{
	return (find_existence(token, T_REDIREC, i));
}

int	syntax_simple_cmd(char **input_cmdline, int *i, int *token, t_cmd **node)
{
	int		pipe_check[2];
	int		pipe_position;

	pipe_check[0] = i[1];
	pipe_check[1] = token_length(token);
	pipe_position = find_index_pipe(token, pipe_check);
	*node = generate_tree(N_SIMPLE_CMD, pipe_position);
	(*node)->l_child = generate_end_node(input_cmdline, N_FILE_PATH,
			i[0], i[0] + 1);
	(*node)->r_child = generate_end_node(input_cmdline, N_ARGV, i[0], i[1]);
	return (1);
}



int	syntax_redirects(char **input_cmdline, int *token, int *i, t_cmd **node)
{
	int	next_redirec_index;
	int	tmp;

	*node = generate_tree(N_REDIREC, -1);
	tmp = i[1];
	next_redirec_index = find_next_redirection(token, i);
	if (next_redirec_index != -1)
		i[1] = next_redirec_index - 1;
	if (syntax_simple_redirect(input_cmdline, i, &((*node)->l_child)) == -1)
		return (-1);
	if (next_redirec_index != -1)
	{
		i[0] = next_redirec_index;
		i[1] = tmp;
		return (syntax_redirects(input_cmdline, token, i, &((*node)->r_child)));
	}
	return (1);
}

/*	[ ]
	[Form & Param]
	syntax_cmds(input_cmdline, token, i, &((*node)->l_child))

	Param(1):	ls -la < file_name | cat -e		// input_cmdline
	Param(2):	W   W  R     W     P  W	  W		// Token from input_cmdline
	   index:	0   1  2     3     4  5   6

	param(3):	Pointer to integer	// Token's sequence
				i[0]: 0				// Index of first token.
				i[1]: 4				// Index of the position of "PIPE".
				= W W R W P

	Param(4):	&(*node)->l_child	// (t_cmd *cmd_tree: NEW_NODE) -> l_child
									// (curr) l_child == NULL;

	[Progress]
	1. tmp = i[1]			// Cpy the index of last token (= first pipe)
	2. generate_tree		// Generate tree struct. (-1: There is no pipe.)
	3. find_index_redirec	// Find the index of redirection.
	4. syntax_simple_cmd	// CMD must have one "SIMPLE CMD".
	5. i[1] = redirec_index // Found RED -> change index of last token.

	[Tree sturct]
			   PIPE
			 /	    \
		   CMD	    PIPE
		  /  \	    /  \
	   	 RED SIM  CMD  PIPE
	  	/   \
	  RED	RED
   	 /   \
   type  file_name
*/
int	syntax_cmds(char **input_cmdline, int *token, int *i, t_cmd **node)
{
	int	redirec_index;
	int	tmp;

	tmp = i[1];
	*node = generate_tree(N_CMD, -1);
	redirec_index = find_index_redirec(token, i);
	if (redirec_index == -1)
	{
		if (syntax_simple_cmd(input_cmdline, i, token, &((*node)->r_child)) != 1)
			return (-1);
	}
	else
	{
		i[1] = redirec_index;
		if (syntax_simple_cmd(input_cmdline, i, token, &((*node)->r_child)) != 1)
			return (-1);
		i[0] = redirec_index;
		i[1] = tmp;
		return (syntax_redirects(input_cmdline, token, i, &((*node)->l_child)));
	}
	return (1);
}

/*	[F]
	Update
*/
void	update_pipe_index(int *i, int pipe_index, int tmp)
{
	i[0] = pipe_index + 1;
	i[1] = tmp;
}

/*	[ ]
	[Form & Param]
	syntax_pipe(validated_token, token, i, &cmd_tree);

	Param(1):	ls -la | cat -e		// input_cmdline
	Param(2):	W  W  P  W  W		// Token from input_cmdline
	param(3):	Pointer to integer	// Token's sequence
				i[0]: 0				// Index of first token.
				i[1]: 5				// Index of last token.
	Param(4):	(cmd_tree)			// From [f] parse_input_cmdline
									// (curr) t_cmd *cmd_tree == NULL;

	[Progress]
	1. find_index_pipe		// Find the position of 'PIPE'
								No 'PIPE'?
								-> Don't need to run this function
								-> Return.

	2. generate_tree(N_CMD)	// Allocate tree struct.
								-> Just declaration
								-> It doesn't point to anything yet.

	3. i[1] = pipe_index;	// Index of last token is changed to 'PIPE'.
								(Before) ls -la | cat -e	// last: "-e"
								(After)	 ls -la |			// last: "|"

	4. pipe_index == i[0]	// 'PIPE' located first -> ERROR.
								(ex) '| ls -la' -> grammatically strange.

	5. syntax_cmds			// Make "l_child" (CMD)
	
	6. update_pipe_index	// Renew the pipe's index

	7. syntax_pipe			// Make "r_child" (PIPE)
*/
int	syntax_pipe(char **input_cmdline, int *token, int *i, t_cmd **node)
{
	int		pipe_index;
	int		tmp;

	tmp = i[1];
	pipe_index = find_index_pipe(token, T_PIPE, i);
	if (pipe_index == -1)
    	return (1);
	else
	{
		*node = generate_tree(N_CMD, pipe_index);
		i[1] = pipe_index;
		if (pipe_index == i[0])
		{
			syntax_pipe_error_print();
			return (-1);
		}
	}
	if (syntax_cmds(input_cmdline, token, i, &((*node)->l_child)) == -1)
		return (-1);
	if (pipe_index != -1)
	{
		update_pipe_index(i, pipe_index, tmp);
		return (syntax_pipe(input_cmdline, token, i, &((*node)->r_child)));
	}
	return (1);
}






int	find_next_redirection(int *token, int *i)
{
	int	index[2];

	index[0] = i[0] + 1;
	index[1] = i[1];
	return (find_existence(token, T_REDIREC, index));
}

char	**text_array_part_cpy(char **line, int start, int end)
{
	int		i;
	char	**part;

	part = (char **)malloc((sizeof(char *)) * (end - start + 1));
	if (!part)
		exit(errno);
	i = 0;
	while (i < end - start)
	{
		part[i] = ft_strdup(line[start + i]);
		if (!part[i])
			exit(errno);
		i ++;
	}
	part[i] = NULL;
	return (part);
}

t_cmd	*generate_end_node(char **line, int type, int start, int end)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	new_node->node_type = type;
	new_node->l_child = NULL;
	new_node->r_child = NULL;
	new_node->cmdstr = text_array_part_cpy(line, start, end);
	new_node->pipe_exist = -1;
	return (new_node);
}

int	syntax_simple_redirect(char **input_cmdline, int *i, t_cmd **node)
{
	*node = generate_tree(N_SIMPLE_REDIREC, -1);
	(*node)->l_child = generate_end_node(input_cmdline, N_REDIREC_TYPE,
			i[0], i[0] + 1);
	(*node)->r_child = generate_end_node(input_cmdline, N_FILE_NAME,
			i[0] + 1, i[1]);
	return (1);
}
