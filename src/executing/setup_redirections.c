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
		close (oldfd);
	close (oldfd);
}

/*
	traverse the t_redirec *stdios linkedlist;
		check the redirect type of node
		open fd->redirect->close oldfd
		if error
			stop traversal and return 1;
*/

int	find_redir(t_redirec *stdios)
{
	t_redirec	*curr;

	curr = stdios;
	while (curr != NULL)
	{
		if (curr->redirec_type == REDIREC_L)
		{
			if (setup_l(curr) != 0)
				return (1);
		}
		else if (curr->redirec_type == REDIREC_LL)
			setup_ll(curr);
		else if (curr->redirec_type == REDIREC_R)
		{
			if (setup_r(curr) != 0)
				return (1);
		}
		else if (curr->redirec_type == REDIREC_RR)
			setup_rr(curr);
		curr = curr->next_redirec;
	}
	return (0);
}

/*
	if the t_redirce node is empty ; return
	find the last left redirection 
	find the last right redirection
	if last left redirec is not null ; setup the last left redirec
	if last right redirec is not null ; setup the last right redirec
*/
int	setup_redirections(t_redirec *stdios)
{
	if (stdios == NULL)
		return (0);
	if (find_redir(stdios) == 0)
		return (0);
	else
		return (1);
}
