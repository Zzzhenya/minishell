/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stage_run_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:50:25 by sde-silv          #+#    #+#             */
/*   Updated: 2024/05/10 14:50:28 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_input(int fd, char *word, t_envp *env, char *line);

int	stage_heredoc(int fd, char *word, t_envp *env, t_tmp *temp)
{
	pid_t		pid;
	int			status;

	pid = 0;
	status = 0;
	pid = fork();
	if (pid == 0)
	{
		heredoc_input(fd, word, env, NULL);
		clear_envlist(env);
		free_things((t_cmd **) NULL, env, env->paths, env->user_input);
		free (temp->name);
		free_for_norminette(temp->arr, temp->token);
		exit (g_exit_status);
	}
	else
	{
		install_signals_child();
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		return (g_exit_status);
	}
}

int	open_run_here(char *word, t_envp *env, t_tmp *temp)
{
	int	fd;
	int	status;

	fd = 0;
	status = 0;
	fd = open(temp->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("bash: Too many heredocs\n");
		g_exit_status = 1;
		return (1);
	}
	status = stage_heredoc(fd, word, env, temp);
	close(fd);
	return (status);
}
