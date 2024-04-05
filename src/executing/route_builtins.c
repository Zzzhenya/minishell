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

/* 
	Builtin router for parent process
*/
void	pid_pid_builtin_n_set(t_cmd *cmd, t_envp *env, pid_t pid)
{
	install_signals(1);
	if (redirection_error_handle(cmd->l_child, pid))
		return ;
	if (!ft_strcmp(cmd->r_child->cmdstr[0], "exit"))
	{
		exec_exit(cmd->r_child->cmdstr, env);
		return ;
	}
	else if (!ft_strcmp(cmd->r_child->cmdstr[0], "unset"))
	{
		exec_unset(cmd->r_child->cmdstr, env);
		return ;
	}
	else if (!ft_strcmp(cmd->r_child->cmdstr[0], "export"))
	{
		exec_export(cmd->r_child->cmdstr, env);
		return ;
	}
	else if (!ft_strcmp(cmd->r_child->cmdstr[0], "cd"))
	{
		exec_cd(cmd->r_child->cmdstr, env, NULL);
		return ;
	}
	if (access(cmd->r_child->cmdstr[0], X_OK) != 0)
		g_exit_status = 127;
}

int	check_builtin(t_cmd *file_path)
{
	if (!ft_strcmp(file_path->cmdstr[0], "echo")
		|| !ft_strcmp(file_path->cmdstr[0], "cd")
		|| !ft_strcmp(file_path->cmdstr[0], "pwd")
		|| !ft_strcmp(file_path->cmdstr[0], "export")
		|| !ft_strcmp(file_path->cmdstr[0], "unset")
		|| !ft_strcmp(file_path->cmdstr[0], "env")
		|| !ft_strcmp(file_path->cmdstr[0], "exit"))
	{
		return (1);
	}
	else
		return (0);
}

/*
	builtin router for child processes
*/
void	builtin_action(t_cmd *builtin, char **cmdline, t_envp *env)
{
	if (!ft_strcmp(builtin->cmdstr[0], "echo"))
		exec_echo(cmdline, 0, NULL);
	else if (!ft_strcmp(builtin->cmdstr[0], "pwd"))
		exec_pwd();
	else if (!ft_strcmp(builtin->cmdstr[0], "env"))
		exec_env(NULL, env);
	exit(errno);
}

void	builtin_router(t_cmd *cmd, t_envp *env, pid_t pid)
{
	if (pid != 0)
		install_signals(1);
	/*if (redirection_error_handle(cmd->l_child, pid))
	{
		if (pid != 0)
			return ;
		else
			exit(g_exit_status);
	}*/
	if (!ft_strcmp(cmd->r_child->cmdstr[0], "exit"))
		exec_exit(cmd->r_child->cmdstr, env);
	else if (!ft_strcmp(cmd->r_child->cmdstr[0], "unset"))
		exec_unset(cmd->r_child->cmdstr, env);
	else if (!ft_strcmp(cmd->r_child->cmdstr[0], "export"))
		exec_export(cmd->r_child->cmdstr, env);
	else if (!ft_strcmp(cmd->r_child->cmdstr[0], "cd"))
		exec_cd(cmd->r_child->cmdstr, env, NULL);
	else if (!ft_strcmp(cmd->r_child->cmdstr[0], "echo"))
		exec_echo(cmd->r_child->cmdstr, 0, NULL);
	else if (!ft_strcmp(cmd->r_child->cmdstr[0], "pwd"))
		exec_pwd();
	else if (!ft_strcmp(cmd->r_child->cmdstr[0], "env"))
		exec_env(NULL, env);
	if (pid == 0)
		exit(g_exit_status);
	else
	{
		return ;
	}
}
