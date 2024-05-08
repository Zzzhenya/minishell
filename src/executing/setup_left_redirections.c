#include "../../include/minishell.h"

/*
	 fd initiated to -1
	 if last_l's redirec type is <
	 	open the last_l->filename in RDONLY mode
		assign the ret value to fd
		 	if fd is 0? ; exit
		duplicate fd and redirect to STDIN
	 if last_l's redirec type is <<
	 	open temp hidden file in O_CREAT | O_WRONLY | O_TRUNC mode 
			O_WRONLY: open for writing only
			O_TRUNC : truncate size to 0
			O_CREAT : create file if it does not exist
			0644 : umask value for the file : I can read and write it; everyone 
			else can only read it. The zero in 0644 says to 
			interpret the number in octal.

			if unable to create file - exit with errno
		read input from the stdin into the temp file, 
			where last_l->filename is the delimiter
		close the opened temp file
		re-open the closed temp file in readonly mode
		duplicate fd of the temp file and redirect it to STDIN
		unlink and delete the temp file and path;
Shouldn't I close the fd? No, dup_and _edirect already closed the old fd

*/

int	setup_l(t_redirec *stdios)
{
	int	fd;

	fd = -1;
	if (stdios->redirec_type == REDIREC_L)
	{
		fd = open(stdios->filename, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(stdios->filename, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			g_exit_status = 1;
			return (1);
		}
		dup_and_redirect(fd, STDIN_FILENO);
	}
	return (0);
}

int	setup_ll(t_redirec *stdios)
{
	int	fd;

	fd = -1;
	if (stdios->redirec_type == REDIREC_LL)
	{
		fd = open(stdios->filename, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(stdios->filename, 2);
			ft_putstr_fd(": Can't find file for heredoc.\n", 2);
			g_exit_status = 1;
			return (1);
		}
		dup_and_redirect(fd, STDIN_FILENO);
		unlink(stdios->filename);
	}
	return (0);
}
