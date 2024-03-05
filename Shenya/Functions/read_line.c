#include "minishell.h"

int get_arg_count(char **argv)
{
	int len = 0;

	while (argv[len])
		len ++;
	return (len);
}

void clean_argv(char **argv, int argc)
{
	int i = 0;

	while (i < argc)
	{
		free (argv[i]);
		argv[i] = NULL;
		i ++;
	}
	free (argv);
	argv = NULL;
}

/* If file is accessible execve the path and options */

int run_command(char **argv)
{
	pid_t	pid;

	if (access(argv[0], 1) != 0)
	{
		printf("%d :Do not have access\n", errno);
		return (1);
	}
	else
		pid = fork();
	if (pid == -1)
	{
		printf("%d :Fork error\n", errno);
		//system("leaks read_line"); 
		return (1);
	}
	if (pid == 0)
	{
		// Do execve stuff to call first command(/bin/ls -la)
		if (execve(argv[0], argv, NULL) == -1)
		{
			printf("%d :execve error\n", errno);
			//system("leaks read_line");
			return (1);
		}
	}
	else
	{
		wait(NULL);
	}
	return (0);
}

int run_command1(char *cmd, char **argv)
{
	pid_t	pid;
	int status;

	if (access(cmd, 1) != 0)
	{
		printf("%d :Do not have access\n", errno);
		return (1);
	}
	else
		pid = fork();
	if (pid == -1)
	{
		printf("%d :Fork error\n", errno);
		//system("leaks read_line"); 
		return (1);
	}
	if (pid == 0)
	{
		// Do execve stuff to call first command(/bin/ls -la)
		/* have to string together cmd and flags as second arg to execve */
		if (execve(cmd, argv, NULL) == -1)
		{
			printf("%d :execve error\n", errno);
			//system("leaks read_line");
			return (1);
		}
	}
	else
	{
		wait(&status);
		//printf("%d\n", status);
	}
	return (0);
}

void	get_env_var(char *name)
{
	char *ret = NULL;

	ret = getenv(name);
	if (ret == NULL)
	{
		printf("%d :getenv error\n", errno);
		return;
	}
	else
		printf("%s\n", ret);
}
/*
int main (void)
{
	char 	*line; 
	char 	**argv;
	int 	argc;

	line = NULL;
	argv = NULL;
	while (1)
	{
		line = readline ("Shell % ");
	
		argv = ft_splitbyspace(line);
		argc = get_arg_count(argv);
		run_command(argv);
		//get_env_var(argv[0]);
		clean_argv(argv, argc);
		free (line);
	}
	//system("leaks read_line"); 
	return (0);
}*/
