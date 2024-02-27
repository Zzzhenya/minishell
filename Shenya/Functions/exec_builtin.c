#include "minishell.h"

void	exec_pwd(void)
{
	char *buf;
	char *retptr;

	buf = malloc(sizeof(char) * 1024);
	if(!buf)
		printf("malloc failed\n");
	buf[1024] = '\0';
	retptr = getcwd(buf, 1024);
	if (!retptr)
	{
		free(buf);
		printf("getcwd crashed\n");
	}
	else
	{
        // Line break after printing to the terminal
        // How to print to terminal?
		printf("%s\n", retptr);
		free (retptr);
	}
}

void    exec_cd(void)
{
    printf("cd\n");
}

void	exec_builtin(char **argv)
{
	if (!ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])))
		exec_pwd();
	else if (!ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])))
		exec_cd();
	else
		printf("%s\n", argv[0]);
}