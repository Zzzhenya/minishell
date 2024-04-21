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

void	builtin_router(t_cmd *cmd, t_envp *env, pid_t pid, int i)
{
	if (redirection_error_handle(cmd->l_child, pid) != 0)
	{
		if (pid != 0)
			return ;
		else
			exit(g_exit_status);
	}
	if (!ft_strcmp(cmd->r_child->cmdstr[0], "exit"))
		exec_exit(cmd->r_child->cmdstr, env, i);
	else if (!ft_strcmp(cmd->r_child->cmdstr[0], "unset"))
		exec_unset(cmd->r_child->cmdstr, env);
	else if (!ft_strcmp(cmd->r_child->cmdstr[0], "export"))
		exec_export(cmd->r_child->cmdstr, env);
	else if (!ft_strcmp(cmd->r_child->cmdstr[0], "cd"))
		exec_cd(cmd->r_child->cmdstr, env, NULL);
	else if (!ft_strcmp(cmd->r_child->cmdstr[0], "echo"))
		exec_echo(cmd->r_child->cmdstr, 0, NULL, env);
	else if (!ft_strcmp(cmd->r_child->cmdstr[0], "pwd"))
		exec_pwd();
	else if (!ft_strcmp(cmd->r_child->cmdstr[0], "env"))
		exec_env(NULL, env);
	if (pid == 0)
		exit(env->arr[i].status);
		//exit(g_exit_status);
	else
	{
		g_exit_status = env->arr[i].status;
		return ;
	}
}
