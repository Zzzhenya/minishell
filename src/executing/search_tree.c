#include "../../include/minishell.h"

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
		If meet with nodes, still have more child nodes, skip node, cause can't execute now.
		
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

void	print_node(t_cmd *node)
{
	int i = 0;

	printf("%d 	", node->pre_flag);
	printf("%d 	", node->pipe_exist);
	if (!node->cmdstr)
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

void	print_leaves(t_cmd *node, char **paths, t_envp *env)
{
	if (!node)
		return;
	if (node && !(node->l_child && node->r_child))
		print_node(node);
	if (node && node->l_child )
		print_leaves(node->l_child, paths, env);
	if (node && node->r_child )
		print_leaves(node->r_child, paths, env);
}

void	search_tree(t_cmd *node, char **paths, t_envp *env)
{
	print_leaves(node, paths, env);

}