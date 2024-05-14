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
	wait for any blocking child processes
	-1 - any childs
	WUNTRACED - 
		return info about terminated children
		return info when child is stopped by signal

	while (waitpid(-1, &status, WUNTRACED) > 0)
	{
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
*/
static void	handle_sig_numbers(int sig, int status, t_envp *env, int i)
{
	(void)status;
	(void)i;
	if ((sig == 2 || sig == 3))
	{
		if (sig == 2)
		{
			printf("\n");
		}
		else
		{
			if (env->procs == 1)
				printf("Quit (core dumped)\n");
		}
	}
}

void	wait_each_command(t_cmd *tree, t_envp *env)
{
	int	status;
	int	i;
	int	sig;

	(void)tree;
	status = 0;
	i = 0;
	sig = 0;
	if (env->procs == 1 && env->builtin == 1)
		return ;
	while (i < env->procs)
	{
		waitpid(env->arr[i].pid, &status, 0);
		if (WIFEXITED(status))
			env->arr[i].status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			env->arr[i].status = 128 + sig;
		}
		i ++;
	}
	handle_sig_numbers(sig, status, env, i);
	g_exit_status = env->arr[i - 1].status;
}
