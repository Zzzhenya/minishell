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
	if (tree->node_type == N_SIMPLE_CMD || tree->node_type == N_REDIREC)
		count ++;
	count = count + count_commands(tree->l_child);
	count = count + count_commands(tree->r_child);
	return (count);
}

/*
	wait for any blocking child processes
	-1 - any childs
	WUNTRACED - 
		return info about terminated children
		return info when child is stopped by signal
*/
void	wait_each_command(t_cmd *tree, t_envp *env)
{
	int	status;
	int i;
	int sig = 0;

	(void)tree;
	status = 0;
	i = 0;
	if (env->cmds == 1 && env->builtin == 1)
		return ;
	if (env->procs == 1 && env->builtin == 1)
		return;
	/*
	while (waitpid(-1, &status, WUNTRACED) > 0)
	{
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}*/
	while (i < env->procs)
	{
		waitpid(env->arr[i].pid, &status, 0);
		if (WIFEXITED(status))
			env->arr[i].status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			env->arr[i].status  = sig;
		}
		//printf("pid: %d , status: %d %s\n", env->arr[i].pid, env->arr[i].status, strsignal(status));
		i ++;
	}
	g_exit_status = env->arr[i - 1].status;
	//printf("status %d\n", g_exit_status);
	if ((sig == 2 || sig == 3)) // (env->cmds != 1) && 
	{
		if (sig == 2)
			printf("\n");
		else
			printf("Quit (core dumped)\n");
		if (status > 0)
			g_exit_status = 128 + status;
		//write(1, "\n", 1);
	}
}
