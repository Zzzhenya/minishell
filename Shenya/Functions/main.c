#include "minishell.h"

int		g_exit_status = 0;
//char *readline (char *prompt);
//char **envp

/* From Jason's pipex */

void	free_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		//arr[i] = NULL;
		i++;
	}
	free (arr);
	//arr = NULL;
}

char	**save_all_env_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(&envp[i][ft_strlen("PATH=")], ':'));
		i++;
	}
	perror("save_all_env_paths: ");
	exit(EXIT_FAILURE);
}

char	*convert_command_absolute_path(char **path_array, int i, char *command)
{
	char	*part_path;
	char	*absolute_path;

	part_path = ft_strjoin(path_array[i], "/");
	if (part_path == NULL)
	{
		perror("ft_strjoin: ");
		return (NULL);
	}
	absolute_path = ft_strjoin(part_path, command);
	free(part_path);
	if (absolute_path == NULL)
	{
		perror("ft_strjoin: ");
		return (NULL);
	}
	return (absolute_path);
}

char	*check_cmd_in_path(char **envp, char *command)
{
	char	**path_array;
	char	*path;
	int		i;

	path_array = save_all_env_paths(envp);
	i = 0;
	while (path_array[i] != NULL)
	{
		if (command[0] != '/')
		{
			path = convert_command_absolute_path(path_array, i, command);
		}
		else
			path = ft_strdup(command);
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
		{
			free_2d(path_array);
			return (path);
		}
		free(path);
		i++;
	}
	free_2d(path_array);
	return (NULL);
}

void	exec_from_path(char **envp, char **argv)
{
	char 	*cmd;

	cmd = NULL;
	cmd = check_cmd_in_path(envp, argv[0]);
	if (!cmd)
	{
		if (errno == 2)
			ft_printf("%s: command not found\n", argv[0]);
		else
		{
			printf("errno %d\n", errno);
			perror("buf_command[0]: ");
		}
	}
	else
	{
		//run_command(argv);
		run_command1(cmd, argv);
	}

}

int cmd_is_builtin(char	**argv)
{
	if (!ft_strncmp(argv[0], "echo", 5)
		|| !ft_strncmp(argv[0], "cd", 3)
		|| !ft_strncmp(argv[0], "pwd", 4)
		|| !ft_strncmp(argv[0], "export", 7)
		|| !ft_strncmp(argv[0], "unset", 6)
		|| !ft_strncmp(argv[0], "env", 4)
		|| !ft_strncmp(argv[0], "exit", 5))
		return (1);
	else
		return (0);
}


/* Need to convert linked list envp to envp arr */
//void	child_process(char **envp, char **argv)
void	child_process(t_envp *my_data, char **argv)
{
	//char **envp;

	//envp = my_data->envarr;
	/*Check whether it's a built in
	if a built in run the built in function
	else convert command to absolute path
	( File names will be coupled with redirections in the struct)
	*/
	if (cmd_is_builtin(argv))
	{
		exec_builtin(argv, my_data);
	}
	else
	{
		extract_envarr(my_data);
		/* handle errors??? What errors? Are they already
		handled by lexer parser? */
		exec_from_path(my_data->envarr, argv);
		free_arr(my_data->envarr, my_data->count);
	}
}


void interactive_bash(char **argv, char *line, int argc, t_envp *my_data)
{
	//char **envp

	//envp = my_data->envp;
	//(void)envp;
	//cmd = NULL;
	install_signals();
	while (1)
	{
		line = readline ("Minishell > ");
		if (line)
			add_history(line);
		/*if (!line)
		{
			// What is the exit code?
			exit (0);
		}*/
		argv = ft_splitbyspace(line);
		argc = get_arg_count(argv);
		//child_process(envp, argv);
		child_process(my_data, argv);
		//get_env_var(argv[0]);
		clean_argv(argv, argc);
		free (line);
		//get_env_var(cmd);
		//ft_printf("errno %d\n", errno);
	}
}

void	non_interactive_bash(char *arg, char **envp)
{
	(void)envp;
	(void)arg;
}


int main (int argc, char **argv, char **envp)
{
	t_envp	my_data;

	my_data.envarr = NULL;
	my_data.cd_hist = NULL;
	my_data.envlist = NULL;
	if (store_envp(&my_data, envp) < 0)
		return (1);
	if (argc == 2)
		non_interactive_bash(argv[1], my_data.envarr);
	else
	{ 
		(void)argc;
		(void)argv;
		/* check if stdin is a tty, why only stdin checked for tty?
			why shouldnt stdin be a tty?*/
		if (isatty(0) == 1)
			interactive_bash(NULL, NULL, 0, &my_data);
		else
			(void)envp;
	}
	/* Need to figure out how to free_arr */
	//free_arr(my_data.envarr, my_data.count);
	//system("leaks minishell"); 
	clear_envlist(&my_data);
	printf("exit: %d\n", g_exit_status);
	return (0);
}
/* Removing error handling for isatty for now because;

sde-silv@c4b11c5$ /bin/bash < a.txt 
sde-silv@c4b11c5$ $?
0: command not found
sde-silv@c4b11c5$ ./minishell < a.txt 
sde-silv@c4b11c5$ $?
25: command not found


*/