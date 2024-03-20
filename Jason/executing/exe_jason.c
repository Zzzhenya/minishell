#include "../../include/minishell.h"

// Finish [ ] out of 12.

/*	[ ]
	ddd

*/
void	update_pipefd(int pipefd[2], int old_input, int pipe_exist)
{
	close(pipefd[0]);
	if (old_input != -1)
		(dup2(old_input, 0));
	if (pipe_exist == -1)
		close(pipefd[1]);
	else
		dup2(pipefd[1], 1);
}

/*	[ ]
	ddd

*/
void	write_pipefd(int pipefd[2], int *old_input, int pipe_exist)
{
	close(pipefd[1]);
	if (*old_input != -1)
		close(*old_input);
	if (pipe_exist == -1)
	{
		close(pipefd[0]);
		*old_input = -1;
	}
	else
		*old_input = pipefd[0];
}

/*	[ ]
	ddd

*/
char	*command_path(char **path_array, int i, char *command)
{
	char	*part_path;
	char	*path;

	part_path = ft_strjoin(path_array[i], "/");
	path = ft_strjoin(part_path, command);
	free(part_path);
	return (path);
}

/*	[ ]
	ddd

*/
char	*path_pointer(char **envp, char *command)
{
	char	*path;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (command[0] != '/')
			path = command_path(envp, i, command);
		else
			path = ft_strdup(command);
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
			return (path);
		free(path);
		i ++;
	}
	return (NULL);
}

/*	[ ]
	ddd

*/
void	print_error_cmd(t_cmd *file_path, char **envp)
{
	char	*path_buf;

	path_buf = path_pointer(envp, file_path->cmdstr[0]);
	if (!path_buf)
	{
		printf("%s: ", file_path->cmdstr[0]);
		if (errno != 2)
			perror("");
		else
			printf("command not found\n");
	}
	free(path_buf);
	return ;
}

/*	[F]
	Search "str" from env, which number of line does it in ENV.

*/
int	find_matching_env_row(char *str, char **env)
{
	int	i;

	i = 0;
	if (str == NULL && *str == '\0')
		return (-1);
	while (env[i] != NULL)
	{
		if (ft_strcmp(env[i], str) != -1)
			return (i); 
		i++;
	}
	return (-1);
}


// pipex that i made. just for reference.
void	exec(char *cmd, char **envp)
{
	char	**cmd_div_space;
	char	*path;

	path = check_cmd_in_path(envp, cmd_div_space[0]);
	if (!path)
		free2d_n_exit(cmd_div_space);
	execve(path, cmd_div_space, envp);
	perror("execve: ");
	if (path)
		free(path);
	free_2d(cmd_div_space);
	exit (EXIT_FAILURE);
}

/*	[ ]

	[Progress]
	1. cmd, cmd[0] == NULL // Nothing to execute -> exit(0)

*/
void	exec(char **cmd, char **env, t_envp *envo)
{
	char	*path;
	int		g_exit_status;

	if (!cmd || !cmd[0])
		exit(0);
	path = NULL;
	if (access(cmd[0], X_OK) == 0)
		path = cmd[0];
	else if (find_matching_env_row("PATH", envo->envp) != -1)
		path = path_pointer(env, cmd[0]);
	if (!path)
		exit(2);
	g_exit_status = execve(path, cmd, env);
	if (path)
		free(path);
	g_exit_status = errno;
	if (g_exit_status)
		exit (errno);
}

/*	[ ]
	ddd

*/
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
}

/*	[ ]
	ddd

*/
void	free_stdios(t_redirec *stdios)
{
	t_redirec	*curr;
	t_redirec	*next;

	curr = stdios;
	while (curr)
	{
		next = curr->next_redirec;
		free(curr);
		curr = next;
	}
}

/*	[ ]
	ddd

*/
void	pid_pid_waiting(t_redirec **stdios)
{
	waitpid(-1, &g_exit_status, WNOHANG);
	if (find_last_in(*(stdios)) != NULL
		&& find_last_in(*(stdios))->redirec_type == REDIREC_LL)
		waitpid(-1, &g_exit_status, 0);
	else
		free_stdios(*stdios);
	*stdios = NULL;
}

/*	[ ]
	ddd

*/
int	redirect_type(t_cmd *node)
{
	if (ft_strcmp(node->cmdstr[0], "<") == 0)
		return (REDIREC_L);
	else if (ft_strcmp(node->cmdstr[0], "<<") == 0)
		return (REDIREC_LL);
	else if (ft_strcmp(node->cmdstr[0], ">") == 0)
		return (REDIREC_R);
	else if (ft_strcmp(node->cmdstr[0], ">>") == 0)
		return (REDIREC_RR);
	return (0);
}


/*	[Reference]
	단순 명령어를 실행하는 역할

	[Progress]
	1. 파이프(pipe)를 생성
	2. 
*/
void	execute_simple_cmd(t_cmd *cmd, t_redirec **stdios, char **envp
		, t_envp *env)
{
	int				pipefd[2];
	static int		old_input = -1;
	pid_t			pid;

	if (pipe(pipefd) == -1)
		return (perror("Pipe: "));
	pid = fork();
	if (pid < 0)
		return (perror("Fork: "));
	else if (pid == 0)
	{
		set_signals_interactive(pid);
		update_redirfd(*stdios);
		update_pipefd(pipefd, old_input, cmd->pipe_exist);
		pid_zero_exec(cmd, envp, env);
	}
	else
	{
		pid_pid_builtin_n_set(cmd, env);
		write_pipefd(pipefd, &old_input, cmd->pipe_exist);
		pid_pid_waiting(stdios);
	}
}

/*	[ ]
	ddd

*/
void	execute_simple_redirect(t_cmd *node, t_redirec **stdios)
{
	t_redirec	*redirection;
	t_redirec	*curr;

	redirection = (t_redirec *)malloc(sizeof(t_redirec));
	if (*stdios == NULL)
	{
		redirection->filename = node->r_child->cmdstr[0];
		redirection->redirec_type = redirect_type(node->l_child);
		redirection->next_redirec = NULL;
		*stdios = redirection;
	}
	else
	{
		redirection->filename = node->r_child->cmdstr[0];
		redirection->redirec_type = redirect_type(node->l_child);
		redirection->next_redirec = NULL;
		curr = *stdios;
		while (curr->next_redirec)
			curr = curr->next_redirec;
		curr->next_redirec = redirection;
	}
}

/*	[?] Reference
	[Progress]
	1. check the NODE'S TYPE
		if Node type is (N_CMD, N_REDIREC)
			return ;
	2. 

*/
void	execute_tree(t_cmd *node, t_redirec **stdios, char **envp, t_envp *envs)
{
	if (node->node_type == N_CMD || node->node_type == N_REDIREC)
		return ;
	else if (node->node_type == N_SIMPLE_CMD)
		execute_simple_cmd(node, stdios, envp, envs);
	else if (node->node_type == N_SIMPLE_REDIREC)
		execute_simple_redirect(node, stdios);
}

/*	[?] Reference

	[Example]
	[f] interactive_mode
		1. *tree = parse_user_input(user_input, env);
						P
				R				W
			W		R		W		R
				W		W				W
		= Already seperated to tokens.

		2. search_tree(*tree, envp, env);
		= Check node's status and decide the direction (left || right).
	
	[Progress]
	1. First "execute_tree"
		(if) curr node is CMD or REDIRECTS
			= skip to the next line in function.
		(else) 
	2. 
	3. 
*/
void	search_tree(t_cmd *node, char **envp, t_envp *env)
{
	static t_redirec	*stdios;

	if (node == NULL)
		return ;
	execute_tree(node, &stdios, envp, env);
	if (node->l_child && (node->l_child->node_type != N_REDIREC_TYPE
			|| node->l_child->node_type != N_FILE_PATH))
		search_tree(node->l_child, envp, env);
	if (node->r_child && (node->r_child->node_type != N_FILE_NAME
			|| node->r_child->node_type != N_ARGV))
		search_tree(node->r_child, envp, env);
}

/*	[F]
	Reference
*/
t_cmd	*parse_user_input(char *user_input, t_envp *env)
{
	t_cmd	*cmd_tree;
	char	**validated_input;
	int		*token;
	int		token_sequence[2];
	int		tmp;

	if (user_input == NULL || user_input[0] == 0)
		return (NULL);
	cmd_tree = NULL;
	validated_input = validate_input(user_input, env->envp);
	if (!validated_input)
		return (NULL);
	replace_exit_status(&validated_input, 0, 0, 0);
	token = token_malloc(validated_input);
	if (!token)
		return (NULL);
	token_sequence[0] = 0;
	token_sequence[1] = check_token_length(token);
	tmp = syntax_pipe(validated_input, token, token_sequence, &cmd_tree);
	if (tmp == -1)
		free_tree(cmd_tree);
	if (tmp == -1)
		return (NULL);
	free_2d(validated_input);
	free(token);
	return (cmd_tree);
}