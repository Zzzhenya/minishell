/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:31:31 by sde-silv          #+#    #+#             */
/*   Updated: 2024/04/04 14:59:27 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_builtin(t_cmd *file_path, t_cmd *cmd)
{
	if (!ft_strcmp(file_path->cmdstr[0], "echo")
		|| !ft_strcmp(file_path->cmdstr[0], "cd")
		|| !ft_strcmp(file_path->cmdstr[0], "pwd")
		|| !ft_strcmp(file_path->cmdstr[0], "export")
		|| !ft_strcmp(file_path->cmdstr[0], "unset")
		|| (!ft_strcmp(file_path->cmdstr[0], "env") && !cmd->r_child->cmdstr[1])
		|| !ft_strcmp(file_path->cmdstr[0], "exit"))
	{
		return (1);
	}
	else
		return (0);
}

/*
	if (redirection_error_handle(cmd->l_child, pid, env) != 0)
	{
		if (pid != 0)
			return ;
		else
		{
			exit(g_exit_status);
		}
	}
*/
void	builtin_router(t_cmd *cmd, t_envp *env, pid_t pid, int i)
{
	if (!ft_strcmp(cmd->r_child->cmdstr[0], "exit"))
		exec_exit(cmd->r_child->cmdstr, env, i);
	else if (!ft_strcmp(cmd->r_child->cmdstr[0], "unset"))
		exec_unset(cmd->r_child->cmdstr, env, i);
	else if (!ft_strcmp(cmd->r_child->cmdstr[0], "export"))
		exec_export(cmd->r_child->cmdstr, env, i);
	else if (!ft_strcmp(cmd->r_child->cmdstr[0], "cd"))
		exec_cd(cmd->r_child->cmdstr, env, NULL, i);
	else if (!ft_strcmp(cmd->r_child->cmdstr[0], "echo"))
		exec_echo(cmd->r_child->cmdstr, i, NULL, env);
	else if (!ft_strcmp(cmd->r_child->cmdstr[0], "pwd"))
		exec_pwd(env, i);
	else if (!ft_strcmp(cmd->r_child->cmdstr[0], "env"))
		exec_env(NULL, env, i);
	if (pid == 0)
		free_stuff_and_exit(env, 1, i);
	else
	{
		g_exit_status = env->arr[i].status;
		return ;
	}
}
