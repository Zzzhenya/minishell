#include "minishell.h"

extern int errno;
//char *readline (char *prompt);

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

int main (void)
{
	pid_t	pid;
	char 	*line; 
	char 	**argv;
	int 	argc;

	line = NULL;
	argv = NULL;
	line = readline ("Shell % ");
	
	argv = ft_splitbyspace(line);
	argc = get_arg_count(argv);
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
		clean_argv(argv, argc);
		free (line);
	}
	//system("leaks read_line"); 
	return (0);
}