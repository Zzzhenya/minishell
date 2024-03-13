/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:11:48 by tkwak             #+#    #+#             */
/*   Updated: 2024/03/13 11:24:07 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

/*	[F]
	[Form & Param]
	syntax_simple_cmd(cmd_line, token, i, &((*node)->r_child))
	Param(1): cmd_line	// user_input
	Param(2): token		// type of token (W, P, R)
	Param(3): *i		// token index // i[0]: 0, i[1]: 2 (pipe's position)
	Param(4): **node	// node_struct from previous function.

	[Progress]
	1. Readjust the range for searching the existence of pipe.
	2. Searching the existence of the pipe.
	3. Allocate "new_node".
	4. Pointer to the l_child & r_child.
*/
int	syntax_simple_cmd(char **cmd_line, int *token, int *i, t_cmd **node)
{
	int		pipe_search_range[2];
	int		pipe_index;

	pipe_search_range[0] = i[1];
	pipe_search_range[1] = check_token_length(token);
	pipe_index = find_index_pipe(token, pipe_search_range);
	*node = create_tree_node(N_SIMPLE_CMD, pipe_index);
	(*node)->l_child = create_leaf_node(cmd_line, N_FILE_PATH, i[0], i[0] + 1);
	(*node)->r_child = create_leaf_node(cmd_line, N_ARGV, i[0], i[1]);
	return (1);
}

/* [F]
	check [f]syntax_simple_cmd (almost same as that function)
*/
int	syntax_simple_redirect(char **cmd_line, int *i, t_cmd **node)
{
	*node = create_tree_node(N_SIMPLE_REDIREC, -1);
	(*node)->l_child
		= create_leaf_node(cmd_line, N_REDIREC_TYPE, i[0], i[0] + 1);
	(*node)->r_child
		= create_leaf_node(cmd_line, N_FILE_NAME, i[0] + 1, i[1]);
	return (1);
}

/* [F]
	check [f]syntax_cmds (almost same as that function)
*/
int	syntax_redirects(char **cmd_line, int *token, int *i, t_cmd **node)
{
	int	tmp;
	int	next_redirec_index;

	tmp = i[1];
	*node = create_tree_node(N_REDIREC, -1);
	next_redirec_index = find_index_next_redirec(token, i);
	if (next_redirec_index == -1)
	{
		if (syntax_simple_redirect(cmd_line, i, &((*node)->l_child)) == -1)
			return (-1);
	}
	else
	{
		i[1] = next_redirec_index - 1;
		if (syntax_simple_redirect(cmd_line, i, &((*node)->l_child)) == -1)
			return (-1);
		i[0] = next_redirec_index;
		i[1] = tmp;
		return (syntax_redirects(cmd_line, token, i, &((*node)->r_child)));
	}
	return (1);
}

/*	[F]
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

	[Tree sturct]
			   PIPE (CMD)
			 /	    \
		   CMD	    PIPE (CMD)
		  /  \	    /  \
	   	 RED SIM  CMD  PIPE (CMD)
	  	/   \
	  RED	RED
   	 /   \
   type  file_name

	[Progress]
	1.	tmp = i[1]			// Cpy the index of last token (= first pipe)
	2.	create_tree_node	// Create tree struct. (-1: There is no pipe in this branch)
	3.	find_index_redirec	// Find the index of redirection.
	4-1.syntax_simple_cmd	// R -> syntax_simple_cmd
							// "SIMPLE_CMD"node must be in right child node from "CMD".
	4-2.Found "REDIREC"		// Change index of last token to the index of redirection.
							// R -> syntax_simple_cmd
							// L -> syntax_redirects
*/
int	syntax_cmds(char **cmd_line, int *token, int *i, t_cmd **node)
{
	int	tmp;
	int	redirec_index;

	tmp = i[1];
	*node = create_tree_node(N_CMD, -1);
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
	[Form & Param]
	syntax_pipe(validated_token, token, i, &cmd_tree);

	Param(1):	ls -la | cat -e		// cmd_line
	Param(2):	W  W  P  W  W		// Token from cmd_line
	param(3):	Pointer to integer	// Token's sequence
				i[0]: 0		// Index of first token.
				i[1]: 5		// Index of last token.
	Param(4):	(cmd_tree)		// From [f] parse_cmd_line
						// (curr) t_cmd *cmd_tree == NULL;

	[Progress]
	1. find_index_pipe		// Find the position of 'PIPE'
						No 'PIPE'?
						-> Don't need to run this function
						-> Return.

	2. create_tree_node(N_CMD)	// Allocate tree struct.
						-> Just declaration
						-> It doesn't point to anything yet.

	3. i[1] = pipe_index;	// Index of last token is changed to 'PIPE'.
				(Before) ls -la | cat -e	// last token: "-e"
				(After)	 ls -la |			// last token: "|"

	4. pipe_index == i[0]	// If 'PIPE' located first -> ERROR.
				  (ex) '| ls -la' -> grammatically strange.

	5. syntax_cmds		// Make "l_child" (CMD)
	6. update_pipe_index	// Renew the pipe's index
	7. syntax_pipe		// Make "r_child" (PIPE) // Recursive function.
*/
int	syntax_pipe(char **cmd_line, int *token, int *i, t_cmd **node)
{
	int	tmp;
	int	pipe_index;

	tmp = i[1];
	*node = create_tree_node(N_CMD, pipe_index);
	pipe_index = find_index_pipe(token, i);
	if (pipe_index == -1)
	{
		if (syntax_cmds(cmd_line, token, i, &((*node)->l_child)) == -1)
			return (-1);
	}
	else
	{
		i[1] = pipe_index;
		if (pipe_index == i[0])
		{
			syntax_pipe_error_print();
			return (-1);
		}
		if (syntax_cmds(cmd_line, token, i, &((*node)->l_child)) == -1)
			return (-1);
		update_pipe_index(i, pipe_index, tmp);
		return (syntax_pipe(cmd_line, token, i, &((*node)->r_child)));
	}
	return (1);
}
