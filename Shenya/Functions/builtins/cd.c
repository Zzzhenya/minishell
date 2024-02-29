#include "../minishell.h"

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
*/

void    exec_cd(char **argv)
{

	if (chdir(argv[1]) == -1)
	{
		g_exit_status = 1;
		ft_putstr_fd("bash: cd: ", 1);
		ft_putstr_fd(argv[1], 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		return;
		//exit(g_exit_status);
	}
	else
	{
		g_exit_status = 0;
		return;
	}
}