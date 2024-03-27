#include "../../include/minishell.h"

int get_arg_count(char **argv)
{
	int len = 0;

	if (!argv)
		return (len);
	while (argv[len])
		len ++;
	return (len);
}

int	count_commands(t_cmd *tree)
{
	int	count;

	if (tree == NULL)
		return (0);
	count = 0;
	if (tree->node_type == N_SIMPLE_CMD)
		count ++;
	count = count + count_commands(tree->l_child);
	count = count + count_commands(tree->r_child);
	return (count);
}

void	wait_each_commands(t_cmd *tree)
{
	int	num_commands;
	int	i;

	num_commands = count_commands(tree);
	i = 0;
	while (i < num_commands)
	{
		waitpid(-1, &g_exit_status, WUNTRACED);
		i ++;
	}
}

/*
void	heredoc_input(int filefd, char *word)
{
	char	*line;
	int		i;

	i = 0;
	line = ft_calloc(1, 1);
	while (ft_strcmp(line, word) != 0)
	{
		free(line);
		line = readline("heredoc> ");
		if (!line)
			exit(1);
		if (ft_strcmp(line, word) != 0)
		{
			write(filefd, line, ft_strlen(line));
			write(filefd, "\n", 1);
		}
		i ++;
	}
	free(line);
}

void	re_type_l_pipes(int filefd)
{
	int	fd_tmp;

	fd_tmp = dup2(filefd, 0);
	if (fd_tmp == -1)
	{
		close(filefd);
		exit(errno);
	}
}

void	connect_last_in(t_redirec *last_in)
{
	int	filefd;

	filefd = -1;
	if (last_in->redirec_type == REDIREC_L)
	{
		filefd = open(last_in->filename, O_RDONLY);
		if (!filefd)
			exit(errno);
		re_type_l_pipes(filefd);
	}
	else if (last_in->redirec_type == REDIREC_LL)
	{
		filefd = open(".___tmp__4heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (!filefd)
			exit(errno);
		heredoc_input(filefd, last_in->filename);
		close(filefd);
		filefd = open(".___tmp__4heredoc", O_RDONLY);
		re_type_l_pipes(filefd);
		unlink(".___tmp__4heredoc");
	}
}

void	re_type_r_pipes(int filefd)
{
	int	fd_tmp;

	fd_tmp = dup2(filefd, 1);
	if (fd_tmp == -1)
	{
		close(filefd);
		exit(errno);
	}
}

void	connect_last_out(t_redirec *last_out)
{
	int	filefd;

	filefd = -1;
	if (last_out->redirec_type == REDIREC_R)
	{
		filefd = open(last_out->filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (filefd == -1)
			exit(errno);
		re_type_r_pipes(filefd);
	}
	else if (last_out->redirec_type == REDIREC_RR)
	{
		filefd = open(last_out->filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (filefd == -1)
			exit(errno);
		re_type_r_pipes(filefd);
	}
	close(filefd);
}

t_redirec	*find_last_out(t_redirec *stdios)
{
	t_redirec	*last_out;
	t_redirec	*curr;

	last_out = NULL;
	curr = stdios;
	while (curr)
	{
		if (curr->redirec_type == REDIREC_R || curr->redirec_type == REDIREC_RR)
			last_out = curr;
		curr = curr->next_redirec;
	}
	return (last_out);
}
*/
/*
t_redirec	*find_last_in(t_redirec *stdios)
{
	t_redirec	*last_in;
	t_redirec	*curr;

	last_in = NULL;
	curr = stdios;
	while (curr)
	{
		if (curr->redirec_type == REDIREC_L || curr->redirec_type == REDIREC_LL)
			last_in = curr;
		curr = curr->next_redirec;
	}
	return (last_in);
}*/
/*
void	update_redirfd(t_redirec *stdios)
{
	t_redirec	*last_in;
	t_redirec	*last_out;

	if (stdios == NULL)
		return ;
	last_in = find_last_in(stdios);
	last_out = find_last_out(stdios);
	if (last_in != NULL)
		connect_last_in(last_in);
	if (last_out != NULL)
		connect_last_out(last_out);
}
*/
int	red_error_handle(t_cmd *type, pid_t pid)
{
	if (type->cmdstr[0][0] == '<' || type->cmdstr[0][0] == '>')
	{
		g_exit_status = 0;
		if (pid == 0)
			exit (g_exit_status);
		else
			return (1);
	}
	else
		return (0);
}

void	pid_pid_builtin_n_set(t_cmd *cmd, t_envp *env)
{
	//set_signals_interactive(1);
	if (red_error_handle(cmd->l_child, 1))
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
        exec_cd(cmd->r_child->cmdstr, env);
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
		|| !ft_strcmp(file_path->cmdstr[0], "/bin/env")
		|| !ft_strcmp(file_path->cmdstr[0], "/usr/bin/env")
		|| !ft_strcmp(file_path->cmdstr[0], "exit"))
		return (1);
	else
		return (0);
}

void	builtin_action(t_cmd *builtin, char **cmdline, t_envp *env)
{
	if (!ft_strcmp(builtin->cmdstr[0], "echo"))
		exec_echo(cmdline);
	else if (!ft_strcmp(builtin->cmdstr[0], "pwd"))
		exec_pwd();
	else if (!ft_strcmp(builtin->cmdstr[0], "env")
		|| !ft_strcmp(builtin->cmdstr[0], "/bin/env")
		|| !ft_strcmp(builtin->cmdstr[0], "/usr/bin/env"))
		exec_env(NULL, env);
	exit(errno);
}