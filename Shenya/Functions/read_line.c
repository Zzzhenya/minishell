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
