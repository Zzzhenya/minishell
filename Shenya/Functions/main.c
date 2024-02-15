#include "minishell.h"

//char *readline (char *prompt);
//char **envp
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
}