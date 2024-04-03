/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:37:59 by sde-silv          #+#    #+#             */
/*   Updated: 2024/04/03 15:38:28 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*	[F]
	[Role]
	If built-in function -> execute [f] "builtin_action".
	Else external function -> execute [f] "exec". (= system call).

	[progress]
	check_builtin
	1. yes	-> builtin_action
	2. no	-> redirection_error_handle [f]red_error_handle
			-> print error message about cmd.
			-> exec
*/
void	pid_zero_exec(t_cmd *cmd, char **envp, t_envp *env, pid_t pid)
{
	if (check_builtin(cmd->l_child))
		builtin_action(cmd->r_child, cmd->r_child->cmdstr, env);
	else
	{
		redirection_error_handle(cmd->l_child, pid);
		print_error_cmd(cmd->l_child, envp);
		exec(cmd->r_child->cmdstr, envp, env);
	}
}
