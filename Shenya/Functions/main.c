#include "minishell.h"

//char *readline (char *prompt);
//char **envp

void interactive_bash(char **argv, char *line, int argc, char **envp)
{
	(void)envp;
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
		interactive_bash(NULL, NULL, 0, envp);
	}
	//system("leaks read_line"); 
	return (0);
}