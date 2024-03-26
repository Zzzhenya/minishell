#include "../../include/minishell.h"

char	*get_pwd(void)
{
	char	*path;

	path = NULL;
	path = getcwd(path, PATH_MAX);
	if (!path)
	{
		g_exit_status = EX_CMD_NOT_FOUND;
		return (NULL);
	}
	else
		return (path);
}

/* When executing pwd should I exit when an error occurs
 and/or when successfully executed?

 is 127 the correct exit code for when getcwd fails? 
 */

void	exec_pwd(void)
{  
	char	*path;

	path = NULL;
	path = get_pwd();
	if (!path)
	{
		//exit(g_exit_status);
		return;
	}
	else
	{
		ft_putstr_fd(path, 1);
		ft_putchar_fd('\n', 1);
		free (path);
	}
	g_exit_status = EXIT_SUCCESS;
	return;
	//exit(g_exit_status);
}