#include "../../include/minishell.h"

// Temporary declaration
extern int	g_exit_status;

NEW					END
1. N_CMD
2. N_SIMPLE_CMD		3. N_FILE_PATH
					4. N_ARGV
5. N_REDIREC
6. N_SIMPLE_REDIREC 7. N_REDIREC_TYPE
					8. N_FILE_NAME

# define N_CMD 1			// Generating new "CMD" tree struct.
# define N_SIMPLE_CMD 2		// Generating new "SIMPLE_CMD" tree struct.
# define N_FILE_PATH 3			// Generating end "FILE_PATH" tree struct.
# define N_ARGV 4				// Generating end "ARGV" tree struct.
# define N_REDIREC 5		// Generating new "REDIREC" tree struct.
# define N_SIMPLE_REDIREC 6	// Generating new "SIMPE_REDIREC" tree struct. // IDK, when i use this.
# define N_REDIREC_TYPE 7		// Generating end "REDIREC_TYPE" tree struct.
# define N_FILE_NAME 8			// Generating end "FILE_NAME" tree struct.
// Every node macro consist of "CMD", staring with CMD and dividing with others.
// # define N_PIPE 1			// No need, but didn't know that.

typedef struct s_cmd
{
	struct s_cmd		*l_child;
	struct s_cmd		*r_child;
	char				**cmdstr;		// Only used for the [f]"generate_end_tree".
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

------------------------------FIND.c------------------------------
/*	[F]	
	[Form & Param]
	find_index_pipe(token, T_PIPE(or T_REDIREC), i);
		Param(1): Array, saves the type of tokens // W P R S D
		Param(2): Target(= T_PIPE)
		Param(3): Pointer to integer from the function("parse_cmd_line")
					i[0]: 0		// Starting
					i[1]: 5		// Length of token

	[Explanaion]
	Find the existence of the "pipe" or the "redirection" among the tokens.
	If found, returns an (INDEX) of position of it.
*/
int	find_existence(int *token, int target, int *i)
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

/*	[F]	
	Target = T_PIPE
*/
int	find_index_pipe(int *token, int *i)
{
	return (find_existence(token, T_PIPE, i));
}

/*	[F]	
	Target = T_REDIREC
*/
int	find_index_redirec(int *token, int *i)
{
	return (find_existence(token, T_REDIREC, i));
}

/*	[F]	
	Target = T_REDIREC
	
	[Explanation]
	index[2] // Order of point
		index[0]: Start point to find the next Redirection.
			i[0] + 1 // next character in same token.
				ex) >>>

		index[1]: End point to find the next Redirection.
			i[1]	 // next token.
*/
int	find_index_next_redirec(int *token, int *i)
{
	int	index[2];

	index[0] = i[0] + 1;
	index[1] = i[1];
	return (find_existence(token, T_REDIREC, index));
}
------------------------------FIND.c------------------------------



--------------------------generate_node.c--------------------------
/*	[F]	
	[Form & Param]
	generate_new_tree(N_CMD, pipe_index);
					2	  position

	[Explanation]
	Generate the new tree node,
	1. Allocate memories as many as "t_cmd".
	2. Initialize the pointer to "l_child" & "r_child" to NULL.
	3. End_tree only needs "cmdstr", not New_tree.
		-> Initialize "cmdstr" to NULL.
	4. Save the data about the "node_type" and "pipe's position"
	   getting the data from parameters.
	5. Every tree has left, right child node.
*/
t_cmd	*generate_new_tree(int type, int pipe_index)
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

/*	[F]	
	Duplicate cmd_line.
	Make the copy cmd_line of the given cmd_line
*/
char	*ft_strdup(const char *str)
{
    int     i;
    char    *res;

    i = 0;
    res = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (res == NULL)
        return (NULL);
    while (str[i] != '\0')
    {
        res[i] = str[i];
        i++;
    }
    res[i] = '\0';
    return (res);
}

/*	[F]	
	[Form & Param]
	new_node->cmdstr = cpy_substring(cmd_line, start, end);
	Param(1): cmd_line // Original string.
	Param(2): start	// Starting index.
	Param(3): end	// End index, representing the position for '\0'.

	[Example]
	res = cpy_substring("abcde", 0, 2);
	res = {"a", "b", "\0"}

	[Progress]
	1. Allocate memory for the result array.
	2. Extract a substring from the original string(= cmd_line, param(1))
		following the specified index range from param(2),(3).
	3. Copy substring from cmd_line(= Original string).

	[FFFFFLAG]
	Include "start" but not include "end".
	"End" must be '\0'.
	"시작은 포함하고 끝은 포함하지 않음"

											start     end
	generate_end_tree(cmd_line, N_FILE_PATH, i[0], i[0] + 1);
	i[0] + 1 // 스타트 문자의 다음 자리에 위치한 문자는 무조건 '\0'처리 된다.
	(ex) ls -la | cat -e
	start:	i[0]: 0
	end:	i[0]+1: 0+1 == 1
		res[0] = "ls";
		res[1] = NULL

									    start  end
	generate_end_tree(cmd_line, N_ARGV, i[0], i[1]);
	(ex) ls -la | cat -e
	start:	i[0]: 0
	end:	i[1]: 2
		res[0] = "ls";
		res[1] = "-la";
		res[2] = NULL;
*/
char	**cpy_substring(char **cmd_line, int start, int end)
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

/*	[F]
	[Form & Param]
	generate_end_tree(char **cmd_line, int type, int start, int end)

	Param(1) **cmd_line		// 
	Param(2) **type			// Which type of the node, do i want to make?
	Param(3) start			// Start index for the field, cmdstr
	Param(4) end			// End index for the filed, cmdstr

	[Progress]
	1. malloc:		Allocates memory to the last node(end-node) of that tree branch.
	2. l,r_child:	Last node don't need child nodes anymore, cause it's ended.
	3. cmdstr:		copy the cmd_line,Param(1) from string to 'cmdstr' in struct.
					Index for [f]cpy_substring is from Param(3)(4).
	4. type:		Save type from param(2)
	5. Pipe_exist:	Don't need to check 'pipe' anymore -> -1.
*/
t_cmd	*generate_end_tree(char **cmd_line, int type, int start, int end)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	new_node->node_type = type;
	new_node->l_child = NULL;
	new_node->r_child = NULL;
	new_node->cmdstr = cpy_substring(cmd_line, start, end);
	new_node->pipe_exist = -1;
	return (new_node);
}

--------------------------generate_node.c--------------------------

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

/*	[ ]
	[Form & Param]
	syntax_simple_cmd(cmd_line, token, i, &((*node)->r_child))
	Param(1): cmd_line	// user_input
	Param(2): token		// type of token (W, P, R)
	Param(3): *i		// token index // i[0]: 0, i[1]: 2 (pipe's position)
	Param(4): node_struct from previous function.

	[Progress]
	1. Checking the existence of pipe.
	2. Allocate "new_node"

*/
int	syntax_simple_cmd(char **cmd_line, int *token, int *i, t_cmd **node)
{
	int		pipe_check[2];
	int		pipe_index;

	pipe_check[0] = i[1];									// 2
	pipe_check[1] = token_length(token);					// 4
	pipe_index = find_index_pipe(token, pipe_check);		// -1
	*node = generate_new_tree(N_SIMPLE_CMD, pipe_index);
	(*node)->l_child = generate_end_tree(cmd_line, N_FILE_PATH,
			i[0], i[0] + 1);
	(*node)->r_child = generate_end_tree(cmd_line, N_ARGV, i[0], i[1]);
	return (1);
}



int	syntax_simple_redirect(char **cmd_line, int *i, t_cmd **node)
{	*node = generate_new_tree(, -1);
	(*node)->l_child = generate_end_tree(cmd_line, N_REDIREC_TYPE,
			i[0], i[0] + 1);
	(*node)->r_child = generate_end_tree(cmd_line, N_FILE_NAME,
			i[0] + 1, i[1]);
	return (1);
}

int	syntax_redirects(char **cmd_line, int *token, int *i, t_cmd **node)
{
	int	next_redirec_index;
	int	tmp;

	*node = generate_new_tree(N_REDIREC, -1);
	tmp = i[1];
	next_redirec_index = find_index_next_redirec(token, i);
	if (next_redirec_index != -1)
		i[1] = next_redirec_index - 1;
	if (syntax_simple_redirect(cmd_line, i, &((*node)->l_child)) == -1)
		return (-1);
	if (next_redirec_index != -1)
	{
		i[0] = next_redirec_index;
		i[1] = tmp;
		return (syntax_redirects(cmd_line, token, i, &((*node)->r_child)));
	}
	return (1);
}

/*	[ ]
	[Form & Param]
	syntax_cmds(cmd_line, token, i, &((*node)->l_child))

	Param(1):	ls -la < file_name | cat -e		// cmd_line
	Param(2):	W   W  R     W     P  W	  W		// Token from cmd_line
	   index:	0   1  2     3     4  5   6

	param(3):	Pointer to integer	// Token's sequence
				i[0]: 0				// Index of first token.
				i[1]: 4				// Index of the position of "PIPE".
				= W W R W P

	Param(4):	&(*node)->l_child	// (t_cmd *cmd_tree: NEW_NODE) -> l_child
									// (curr) l_child == NULL;

	[Progress]
	1. tmp = i[1]			// Cpy the index of last token (= first pipe)
	2. generate_new_tree	// Generate tree struct. (-1: There is no pipe, pipe is always right side.)
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
int	syntax_cmds(char **cmd_line, int *token, int *i, t_cmd **node)
{
	int	redirec_index;
	int	tmp;

	tmp = i[1];
	*node = generate_new_tree(N_CMD, -1);
	redirec_index = find_index_redirec(token, i);
	if (redirec_index == -1)
	{
		if (syntax_simple_cmd(cmd_line, token, i, &((*node)->r_child)) != 1)
			return (-1);
	}
	else
	{
		i[1] = redirec_index;
		if (syntax_simple_cmd(cmd_line, token, i, &((*node)->r_child)) != 1)
			return (-1);
		i[0] = redirec_index;
		i[1] = tmp;
		return (syntax_redirects(cmd_line, token, i, &((*node)->l_child)));
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

	Param(1):	ls -la | cat -e		// cmd_line
	Param(2):	W  W  P  W  W		// Token from cmd_line
	param(3):	Pointer to integer	// Token's sequence
				i[0]: 0				// Index of first token.
				i[1]: 5				// Index of last token.
	Param(4):	(cmd_tree)			// From [f] parse_cmd_line
									// (curr) t_cmd *cmd_tree == NULL;

	[Progress]
	1. find_index_pipe		// Find the position of 'PIPE'
								No 'PIPE'?
								-> Don't need to run this function
								-> Return.

	2. generate_new_tree(N_CMD)	// Allocate tree struct.
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
// Reference
t_cmd	*generate_new_tree(int type, int pipe_index)
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