#include "../../include/minishell.h"

/*
	initiate fd to -1
	if last_r redirec_type is REDIREC_R  // >
		open the given filename in O_WRONLY | O_CREAT | O_TRUNC, 0666 mode
		O_WRONLY - Write Only
		O_CREAT - Create if not available
		O_TRUNC - truncate size to 0
		0666 - Grants read and write permission to everyone.
		if open fails, exit and set errno;
		duplicate fd of the opened file and redirect it to STDOUT
	if last_r redirec_type is REDIREC_RR - Append  // >>
		open the given filename in O_WRONLY | O_CREAT | O_APPEND, 0666 mode
		O_WRONLY - Write Only
		O_CREAT - Create if not available
		O_APPEND - Append to the end
		0666 - Grants read and write permission to everyone.
		if open fails, exit and set errno;
		duplicate fd of the opened file and redirect it to STDOUT
			 - > this closed old fd
*/

int	setup_r(t_redirec *stdios)
{
	int	fd;

	fd = -1;
	if (stdios->redirec_type == REDIREC_R)
	{
		fd = open(stdios->filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
		{
			printf("bash: %s: Open error\n", stdios->filename);
			g_exit_status = errno;
			return (1);
		}
		dup_and_redirect(fd, STDOUT_FILENO);
	}
	return (0);
}

int	setup_rr(t_redirec *stdios)
{
	int	fd;

	fd = -1;
	if (stdios->redirec_type == REDIREC_RR)
	{
		fd = open(stdios->filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd == -1)
		{
			printf("bash: %s: Open error\n", stdios->filename);
			g_exit_status = errno;
			return (1);
		}
		dup_and_redirect(fd, STDOUT_FILENO);
	}
	return (0);
}
