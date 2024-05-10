/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_and_run_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:46:22 by sde-silv          #+#    #+#             */
/*   Updated: 2024/05/09 17:53:46 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_input(int fd, char *word, t_envp *env, char *line);
/*

# define T_NULL 0
# define T_WORD 1
# define T_PIPE 2
# define T_REDIREC 3
# define T_S_QUOTE 4
# define T_D_QUOTE 5

*/

int	stage_heredoc(int fd, char *word, t_envp *env, t_tmp *temp)
{
	pid_t		pid;
	int			status;

	pid = 0;
	status = 0;
	//(void)env;
	pid = fork();
	if (pid == 0)
	{
		heredoc_input(fd, word, env, NULL);
		clear_envlist(env);
		if (env->envarr)
			free_arr(env->envarr, get_arg_count(env->envarr));
		if (env->paths)
			free_2d(env->paths);
		if (temp)
		{
			free(temp->name);
			free_for_norminette(temp->arr, temp->token);
		}
		exit(g_exit_status);
	}
	else
	{
		install_signals_child();
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		// else if (WIFSIGNALED(status))
		// 	g_exit_status = WTERMSIG(status);
		return (g_exit_status);
	}
}

char	*get_heredoc_name(int count)
{
	char	*ret;
	char	*name;

	name = NULL;
	ret = NULL;
	ret = ft_itoa(count);
	name = ft_strjoin(HEREDOCNAME, ret);
	free (ret);
	return (name);
}

int	cleanup_heredocs(int count)
{
	char	*name;

	name = NULL;
	while (count > 0)
	{
		name = get_heredoc_name(count);
		unlink(name);
		count --;
		free (name);
	}
	return (1);
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

int	setup_and_run_heredoc(int *token, char **arr, t_envp *env)
{
	int		i;
	int		count;
	// char	*name;
	int		status;
	t_tmp	temp;

	i = 0;
	count = 1;
	// name = NULL;
	status = 0;
	temp.arr = arr;
	temp.token = token;
	temp.name = NULL;
	while (arr[i])
	{
		if (*token == T_REDIREC && !ft_strncmp(arr[i], "<<", 3))
		{
			temp.name = get_heredoc_name(count);
			status = open_run_here(arr[i + 1], env, &temp);
			count ++;
			free(arr[i + 1]);
			arr[i + 1] = ft_strdup(temp.name);
			free (temp.name);
			temp.name = NULL;
			if (status != 0)
				return (cleanup_heredocs(count));
		}
		i ++;
		token ++;
	}
	return (0);
}
