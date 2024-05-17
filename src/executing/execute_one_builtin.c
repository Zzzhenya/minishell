/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:44:33 by sde-silv          #+#    #+#             */
/*   Updated: 2024/05/09 13:44:34 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_one_builtin_cmd(t_cmd *cmd, t_redirec **stdios, t_envp *env, int i)
{
	env->saved_stdin = dup(STDIN_FILENO);
	close(STDIN_FILENO);
	env->saved_stdout = dup(STDOUT_FILENO);
	close(STDOUT_FILENO);
	env->builtin = 1;
	if (setup_redirections(*stdios) == 0)
	{
		clean_stdios_list(stdios);
		if (cmd->r_child->cmdstr[0] != NULL)
			builtin_router(cmd, env, 1, i);
	}
	else
		clean_stdios_list(stdios);
	dup2(env->saved_stdout, STDOUT_FILENO);
	close(env->saved_stdout);
	dup2(env->saved_stdin, STDIN_FILENO);
	close(env->saved_stdin);
	return ;
}
