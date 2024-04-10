/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_blocked_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:09:31 by sde-silv          #+#    #+#             */
/*   Updated: 2024/04/10 16:18:17 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	initiate count to 0;
	if the tree is empty 
		return 0 - no children is 0
	if the node_type is N_SIMPLE_CMD
		count
	recursively count & add commands in left sub trees
	recursively count & add commands in right sub trees
	return the total count
*/
int	count_commands(t_cmd *tree)
{
	int	count;

	count = 0;
	if (tree == NULL)
		return (0);
	if (tree->node_type == N_SIMPLE_CMD)
		count ++;
	count = count + count_commands(tree->l_child);
	count = count + count_commands(tree->r_child);
	return (count);
}

/*
	wait for any blocking child processes
	-1 - any child
	WUNTRACED - 
		return info about terminated children
		return info when child is stopped by signal
*/
void	wait_each_command(t_cmd *tree, t_envp *env)
{
	int	status;

	(void)tree;
	if (env->cmds == 1 && env->builtin == 1)
		return ;
	while (waitpid(-1, &status, WUNTRACED) > 0)
	{
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
}
