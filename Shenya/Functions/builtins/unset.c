#include "../minishell.h"

void    exec_unset(char **argv, t_envp *my_data)
{
	// go through the envp list
		// if the variable name exists in the envp list
			// if the variable after is null
				// unset the variable by making it null
			// if variable after is not null;
				// find the last variable
				// make current variable pointer point to the last variable value;
				// unset the last variable by making it null
	(void)argv;
	(void)my_data;
}