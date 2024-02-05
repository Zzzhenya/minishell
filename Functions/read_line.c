#include "minishell.h"

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
	char *line = NULL; 
	char **argv = NULL;
	int argc;

	//printf("%s\n", line);
	line = readline ("Shell % ");
	
	argv = ft_splitbyspace(line);
	argc = get_arg_count(argv);
	//if (argc >= 1)
	if (execve(argv[0], argv, NULL) == -1)
		return (1);
	clean_argv(argv, argc);
	// Do execve stuff to call first command(/bin/ls -la)
	free (line);
	return (0);
}