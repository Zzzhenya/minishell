#include "minishell.h"

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
		i++;
	}
	free (arr);
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
			path = convert_command_absolute_path(path_array, i, command);
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


void interactive_bash(char **argv, char *line, int argc, char **envp)
{
	char 	*cmd;

	(void)envp;
	cmd = NULL;
	while (1)
	{
		line = readline ("Shell % ");
	
		argv = ft_splitbyspace(line);
		argc = get_arg_count(argv);
		cmd = check_cmd_in_path(envp, argv[0]);
		if (!cmd)
		{
			if (errno == 2)
				ft_printf("%s: command not found\n", argv[0]);
			else
				perror("buf_command[0]: ");
		}
		else
		{
			printf("%s\n", cmd);
			//run_command(argv);
			run_command1(cmd, argv);
		}
		//get_env_var(argv[0]);
		clean_argv(argv, argc);
		free (line);
		ft_printf("errno %d\n", errno);
	}
}

void	non_interactive_bash(char *arg, char **envp)
{
	(void)envp;
	(void)arg;
}


int main (int argc, char **argv, char **envp)
{
	if (argc == 2)
		non_interactive_bash(argv[1], envp);
	else
	{ 
		(void)argc;
		(void)argv;
		/* check if stdin is a tty*/
		if (isatty(0) == 1)
			interactive_bash(NULL, NULL, 0, envp);
		else
		{
			(void)envp;
			/* Errno from isatty() */
			return(errno);
		}
	}
	//system("leaks minishell"); 
	return (0);
}