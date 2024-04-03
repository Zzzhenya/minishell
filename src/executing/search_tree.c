#include "../../include/minishell.h"
/*	[F]
	[Role]
	Check the NODE'S TYPE, execute next tree node,
	corresponding to the certain node type.

	[Korean]
	1. 트리의 노드를 실행.
	2. 노드타입에 따라 각기 다른 동작 수행.
	3. 간단명령: execute_simple_cmd 함수호출.
	4. 리다이렉션: execute_simple_redirect 함수호출.

	[Available types for cild_node]
	1. N_SIMPLE_CMD
		LEFT: file_path
		RIGHT: argv
	2. N_SIMPLE_REDIREC
		LEFT: type
		RIGHT: file_name

	[Progress]
	1. If node's type == (N_CMD, N_REDIREC)
		= "there are more redirects and pipes that need to be handled first."
		= return ; // nothing happen.

	2. If node's type == (N_SIMPLE_CMD)
		execute_simple_cmd

	3. If node's type == (N_SIMPLE_REDIREC)
		execute_simple_redirect

	[Struct]
						  N_CMD(1)			|			N_CMD(2)
					/				\
			N_REDIREC				N_SIMPLE_CMD
			/		\					/			\
	N_REDIREC	N_SIMPLE_REDIREC	N_FILE_PATH		N_ARGV
					/		\
		N_REDIREC_TYPE		N_FILE_NAME

*/
void	execute_tree(t_cmd *node, t_redirec **stdios, char **envp, t_envp *envs)
{
	if (node->node_type == N_CMD || node->node_type == N_REDIREC)
		return ;
	else if (node->node_type == N_SIMPLE_CMD)
		execute_simple_cmd(node, stdios, envp, envs);
	else if (node->node_type == N_SIMPLE_REDIREC)
		execute_simple_redirect(node, stdios);
}

/*	[F]
	[Role]
	It receives a parsed tree, traverses that tree struct,
	executres cmds and handles file redirection and pipes.

	[Korean]
	1. 파싱된 트리를 받아 순회하며 명령 실행 & 리다이렉션 처리.
	2. 트리 각 노드를 방문 -> 각 노드 타입 확인 -> 적절한 동작 수행.
	3. 바로 실행 가능한 노드인지 체크, 가능하다면 실행.
	4. 자식 노드 있다면 해당 자식 노드 방문.

	[Key]
	Order: left-first traversal
	To process the left child node first -> and then the right child node.

	[Struct]
						  N_CMD
					/				\
			N_REDIREC				N_SIMPLE_CMD
			/		\					/			\
	N_REDIREC	N_SIMPLE_REDIREC	N_FILE_PATH		N_ARGV
					/		\
		N_REDIREC_TYPE		N_FILE_NAME

	[Progress]
	1. "execute_tree"
		If meet with nodes, still have more child nodes,
			skip node, cause can't execute now.
		
		(if) curr node is (CMD) or (REDIRECTS)
			= Skip to the next node, cause current node couldn't be executed.

		(else) curr node is (N_SIMPLE_CMD) or (N_SIMPLE_REDIREC)
			= Execute node right away, cause it could be executed.

	2. if (left child's node_type != SIMPLE_CMD, SIMPLE_REDIREC)
		There is more nodes from l_child's node
		= search more about l_child node.

	3. if (right child's node_type != SIMPLE_CMD, SIMPLE_REDIREC)
		There is more nodes from r_child's node
		= search more about r_child node.
*/
void	search_tree(t_cmd *node, char **envp, t_envp *env)
{
	static t_redirec	*stdios;

	if (node == NULL)
		return ;
	execute_tree(node, &stdios, envp, env);
	if (node->l_child && (node->l_child->node_type != N_REDIREC_TYPE
			|| node->l_child->node_type != N_FILE_PATH))
		search_tree(node->l_child, envp, env);
	if (node->r_child && (node->r_child->node_type != N_FILE_NAME
			|| node->r_child->node_type != N_ARGV))
		search_tree(node->r_child, envp, env);
}

/*	[F]
	[Example]
	1. *tree = parse_user_input(user_input, env);
					P
			R				W
		W		R		W		R
			W		W				W
	= Already seperated to tokens.

	2. search_tree(*tree, envp, env);
	= Check node's status and decide the direction (left || right).

	3. Follow tree and execute corresponding nodes.

	4. No more tree to execute (= finish to search tree)
		-> free_tree(tree)
		-> free_2d(user_input)

void	non_interactive_mode(t_cmd **tree,
								char *input, char **envp, t_envp *env)
{
	char	**user_inputs;
	int		i;

	user_inputs = ft_split(input, ';');
	i = 0;
	while (user_inputs[i])
	{
		*tree = parse_user_input(user_inputs[i], env);
		search_tree(*tree, envp, env);
		i++;
		free_tree(*tree);
	}
	free_2d(user_inputs);
}
*/