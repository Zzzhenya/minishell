/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_create_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:11:56 by tkwak             #+#    #+#             */
/*   Updated: 2024/03/13 11:11:58 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

/*	[F]
	[Form & Param]
	create_tree_node(N_CMD, pipe_index);

	[Description]
	Generate the new tree node
	1. Allocate memories as many as "t_cmd".
	2. Initialize the pointer to "l_child" & "r_child" to NULL.
	3. End_tree only needs "cmdstr", not New_tree.
		-> Initialize "cmdstr" to NULL.
	4. Save the data about the "node_type" and "pipe's position"
	   getting the data from parameters.
	5. Every tree has left, right child node.

	= 새로운 트리 노드를 생성
*/
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

/*	[F]	
	[Form & Param]
	new_node->cmdstr = copy_substring_range(cmd_line, start, end);
	Param(1): cmd_line // Original string.
	Param(2): start	// Starting index.
	Param(3): end	// End index, representing the position for '\0'.

	[Example]
	res = copy_substring_range("abcde", 0, 2);
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
	create_leaf_node(cmd_line, N_FILE_PATH, i[0], i[0] + 1);
	i[0] + 1 // 스타트 문자의 다음 자리에 위치한 문자는 무조건 '\0'처리 된다.
	(ex) ls -la | cat -e
	start:	i[0]: 0
	end:	i[0]+1: 0+1 == 1
		res[0] = "ls";
		res[1] = NULL

									    start  end
	create_leaf_node(cmd_line, N_ARGV, i[0], i[1]);
	(ex) ls -la | cat -e
	start:	i[0]: 0
	end:	i[1]: 2
		res[0] = "ls";
		res[1] = "-la";
		res[2] = NULL;
*/
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

/*	[F]
	[Form & Param]
	create_leaf_node(char **cmd_line, int type, int start, int end)

	Param(1) **cmd_line		// 
	Param(2) **type			// Which type of the node, do i want to make?
	Param(3) start			// Start index for the field, cmdstr
	Param(4) end			// End index for the filed, cmdstr

	[Progress]
	1. malloc:		Allocates memory to the last node(end-node) of that tree branch.
	2. l,r_child:	Last node don't need child nodes anymore, cause it's ended.
	3. cmdstr:		copy the cmd_line,Param(1) from string to 'cmdstr' in struct.
					Index for [f]copy_substring_range is from Param(3)(4).
	4. type:		Save type from param(2)
	5. Pipe_exist:	Don't need to check 'pipe' anymore -> -1.

	= 리프 노드를 생성
*/
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
