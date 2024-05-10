/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:51:31 by sde-silv          #+#    #+#             */
/*   Updated: 2024/05/07 15:51:33 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_here(int sig)
{
	(void)sig;
	g_exit_status = 130;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	// rl_on_new_line();
	//write (1, "\n", 1);
	// rl_replace_line ("", 0);
	// rl_redisplay();
	//return;
	//exit (g_exit_status);
}

/*
	signal definitions for the heredoc
*/

void	install_signals_here(void)
{
	struct sigaction	act1;
	struct sigaction	act2;

	ft_bzero(&act1, sizeof(act1));
	ft_bzero(&act2, sizeof(act2));
	act1.sa_handler = SIG_IGN;
	act2.sa_handler = &handle_here;
	sigaction(SIGQUIT, &act1, NULL);
	sigaction(SIGINT, &act2, NULL);
}
