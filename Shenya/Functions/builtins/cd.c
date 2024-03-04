#include "../minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
/*

cd [-L|-P] [direcory]
cd -

cd nonexisting_dir/file 
bash: cd: b: No such file or directory -> bash: 1: command not found

cd exiting dir/nonexistant dir or file 
bash: cd: Functions/haha: No such file or directory -> bash: 1: command not found


cd exiting_file
bash: cd: Makefile: Not a directory -> bash: 1: command not found

chmod 666 dirname
cd restricted_dir
bash: cd: restricted: Permission denied -> bash: 1: command not found

cd builtins(dir) -> bash: 0: command not found

cd Functions/builtins/ -> bash: 0: command not found

cd /

cd /sdas/sads/ the absolute path

cd ~

cd

cd ..

cd ~-

cd -

cd +

*/

/*


int 	chdir(const char *path);

The path argument points to the pathname of a directory.  
The chdir()
     function causes the named directory to become the current working
     directory, that is, 
     the starting point for path searches of pathnames not
     beginning with a slash, ‘/’.
  In order for a directory to become the current directory, a process must
     have execute (search) access to the directory.

RETURN VALUES
     Upon successful completion, a value of 0 is returned.  Otherwise, a value
     of -1 is returned and errno is set to indicate the error.


if (S_ISDIR(statbuf.st_mode))
*/

int  not_a_dir(char	*path)
{
	struct	stat statbuf;

	stat(path, &statbuf);
	if (S_ISREG(statbuf.st_mode))
		return (1);
	else
		return (0);
}

void	print_cd_error(char *path, char *message)
{
	ft_putstr_fd("bash: cd: ", 1);
	ft_putstr_fd(path, 1);
	ft_putstr_fd(message, 1);
}

/* 

Should I use local env or call and get new env?
What if HOME in global env has changed ?
 */

char		*change_to_home(t_envp	*my_data)
{
	int		i;
	char		*temp;
	char		*path;

	temp = NULL;
	path = NULL;
	i = 0;
	while (my_data->envp[i] != NULL)
	{
		if (!ft_strncmp(my_data->envp[i], "HOME=", ft_strlen("HOME=")))
			temp = my_data->envp[i];
		i ++;
	}
	if (!temp)
		return (NULL);
	while (*temp)
	{
		if (*temp == '/')
		{
			path = ft_strdup(temp);
			break;
		}
		temp ++;
	}
	return (path);
}

void		execute_path(char	*path)
{
	if (not_a_dir(path))
	{
		g_exit_status = 1;
		print_cd_error(path, ": Not a directory\n");
		free(path);
		return;
	}
	else if (chdir(path) == -1)
	{
		g_exit_status = 1;
		if (errno == EACCES)
			print_cd_error(path, ": Permission denied\n");
		else
			print_cd_error(path, ": No such file or directory\n");
		free(path);
		return;
		//exit(g_exit_status);
	}
	else
	{
		g_exit_status = 0;
		free(path);
		return;
	}

}


/* Why is there a sigsev for cd without parameter? */

void    exec_cd(char **argv, t_envp *my_data)
{
	char *path;

	path = NULL;
	if (my_data->cd_hist != NULL && !ft_strncmp(argv[1], "-", ft_strlen(argv[1])))
	{
		path = my_data->cd_hist;
		printf("%s\n",path);
	}
	else if (my_data->cd_hist == NULL && !ft_strncmp(argv[1], "-", ft_strlen(argv[1])))
	{
		g_exit_status = 1;
		print_cd_error(path, ": OLDPWD not set\n");
		free(path);
		return;
	}
	else if (argv[1] == NULL || ft_strncmp(argv[1], "~", ft_strlen(argv[1])) == 0)
		path = change_to_home(my_data);
	else
		path = argv[1];
	//if (my_data->cd_hist == NULL)
	my_data->cd_hist = get_pwd();
	execute_path(path);
}