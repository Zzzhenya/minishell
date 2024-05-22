/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 21:29:29 by sde-silv          #+#    #+#             */
/*   Updated: 2024/04/10 16:46:59 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_prompt(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line ("", 0);
	rl_redisplay();
}

void	handle_bs(int sig)
{
	write (1, "\n", 1);
	g_exit_status = sig;
	return ;
}

/* 	
	signal definitions for 
		the main before executing 
		the child after executing
*/
void	install_signals_main(int c)
{
	struct sigaction	act1;
	struct sigaction	act2;

	ft_bzero(&act1, sizeof(act1));
	ft_bzero(&act2, sizeof(act2));
	if (c == 10)
		act1.sa_handler = SIG_IGN;
	else
		act1.sa_handler = &handle_bs;
	act2.sa_handler = &handle_prompt;
	sigaction(SIGQUIT, &act1, NULL);
	sigaction(SIGINT, &act2, NULL);
}

/*
	signal definitions for
		the main after executing
*/

void	install_signals_child(void)
{
	struct sigaction	act1;
	struct sigaction	act2;

	ft_bzero(&act1, sizeof(act1));
	ft_bzero(&act2, sizeof(act2));
	act1.sa_handler = SIG_IGN;
	act2.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act1, NULL);
	sigaction(SIGINT, &act2, NULL);
}
