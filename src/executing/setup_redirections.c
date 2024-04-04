/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:40:20 by sde-silv          #+#    #+#             */
/*   Updated: 2024/04/03 15:46:56 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	make a line  of char size of 1
	continue while the line doesn't have/ is not equal to the delimiter word
		free line
		readline into line
		if readline returns a null line; exit
		check whether the line has delimeter word
			if line desn't have the delimiter;
			write line to fd;
			write line break to fd
		increment i??
	When exiting the while loop free line

void	heredoc_input(int fd, char *word)
{
	char	*line;
	int		i;

	i = 0;
	line = ft_calloc(1, 1);
	while (ft_strcmp(line, word) != 0)
	{
		free(line);
		line = readline("heredoc> ");
		if (!line)
			exit(1);
		if (ft_strcmp(line, word) != 0)
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		i ++;
	}
	free (line);
}
	declare a temporary fd integer
	makes a duplicate of the file descriptor fd using the supplied fd
	if dup2 fails; ret = -1, close opened file fd and exit with errno;

*/
void	dup_and_redirect(int oldfd, int newfd)
{
	int	ret;

	ret = -1;
	ret = dup2 (oldfd, newfd);
	if (ret == -1)
	{
		close (oldfd);
		exit (errno);
	}
}

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
	close opened fd
*/
void	setup_last_r(t_redirec *last_r)
{
	int	fd;

	fd = -1;
	if (last_r->redirec_type == REDIREC_R)
	{
		fd = open(last_r->filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			exit(errno);
		dup_and_redirect(fd, STDOUT_FILENO);
	}
	else if (last_r->redirec_type == REDIREC_RR)
	{
		fd = open(last_r->filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd == -1)
			exit(errno);
		dup_and_redirect(fd, STDOUT_FILENO);
	}
	close(fd);
}

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
Shouldn't I close the fd?

*/
void	setup_last_l(t_redirec *last_l)
{
	int	fd;

	fd = -1;
	if (last_l->redirec_type == REDIREC_L)
	{
		fd = open(last_l->filename, O_RDONLY);
		if (!fd)
			exit(errno);
		dup_and_redirect(fd, STDIN_FILENO);
		close(fd);
	}
	else if (last_l->redirec_type == REDIREC_LL)
	{
		fd = open(HEREDOCNAME, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (!fd)
			exit(errno);
		heredoc_input(fd, last_l->filename);
		close(fd);
		fd = open(HEREDOCNAME, O_RDONLY);
		dup_and_redirect(fd, STDIN_FILENO);
		unlink(HEREDOCNAME);
	}
}

t_redirec	*find_last(t_redirec *stdios, char c, t_redirec *last)
{
	t_redirec	*curr;

	curr = stdios;
	if (c == 'l')
	{
		while (curr)
		{
			if (curr->redirec_type == REDIREC_L
				|| curr->redirec_type == REDIREC_LL)
				last = curr;
			curr = curr->next_redirec;
		}
	}
	else if (c == 'r')
	{
		while (curr)
		{
			if (curr->redirec_type == REDIREC_R
				|| curr->redirec_type == REDIREC_RR)
				last = curr;
			curr = curr->next_redirec;
		}
	}
	return (last);
}

/*
	if the t_redirce node is empty ; return
	find the last left redirection 
	find the last right redirection
	if last left redirec is not null ; setup the last left redirec
	if last right redirec is not null ; setup the last right redirec
*/
void	setup_redirections(t_redirec *stdios)
{
	t_redirec	*last_l;
	t_redirec	*last_r;

	if (stdios == NULL)
		return ;
	last_l = find_last(stdios, 'l', NULL);
	last_r = find_last(stdios, 'r', NULL);
	if (last_l != NULL)
		setup_last_l(last_l);
	if (last_r != NULL)
		setup_last_r(last_r);
}
