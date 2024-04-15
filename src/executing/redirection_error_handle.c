/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_error_handle.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:22:29 by sde-silv          #+#    #+#             */
/*   Updated: 2024/04/03 16:22:31 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
WHY?

Why check PID when we are sending a hardcoded pid value
Why check this without printing the error
	printf("bash: syntax error near unexpected token `newline'\n");
What about when the first string of node->cmdstr is << or >>

	if first string of node->cmdstr is < or >
		set exit status to 0
	 		if chid process exit g_exit_status
	 		if parent process return 1
	else return 0

exit status in mac is 258 check for linux	

*/

void	redir_error_msg(void)
{
	g_exit_status = 2;
	printf("bash: syntax error near unexpected token `newline'\n");
}

int	redirection_error_handle(t_cmd *type, pid_t pid)
{
	if (type->cmdstr[0][0] == '<' || type->cmdstr[0][0] == '>')
	{
		g_exit_status = 2;
		if (pid == 0)
		{
			printf("bash: syntax error near unexpected token `newline'\n");
			exit (g_exit_status);
		}
		else
			return (1);
	}
	else
		return (0);
}
