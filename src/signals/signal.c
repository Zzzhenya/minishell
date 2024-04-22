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
/*
void	handle_nl(int sig)
{
	(void)sig;
	write (1, "\n", 1);
}

	signal definitions for 
	the main process after executing
	when the child process hangs

void	install_signals_hang(void)
{
	struct sigaction	act1;
	struct sigaction	act2;

	ft_bzero(&act1, sizeof(act1));
	ft_bzero(&act2, sizeof(act2));
	act1.sa_handler = SIG_IGN;
	act2.sa_handler = &handle_nl;
	sigaction(SIGQUIT, &act1, NULL);
	sigaction(SIGINT, &act2, NULL);
}
*/
void	handle_prompt(int sig)
{
	(void)sig;
	//g_exit_status = 130;
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line ("", 0);
	rl_redisplay();
}

/* 	
	signal definitions for 
		the main before executing 
		the child after executing
*/
void	install_signals_main(void)
{
	struct sigaction	act1;
	struct sigaction	act2;

	ft_bzero(&act1, sizeof(act1));
	ft_bzero(&act2, sizeof(act2));
	act1.sa_handler = SIG_IGN;
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

void	handle_here(int sig)
{
	(void)sig;
	write (1, "\n", 1);
	exit(130);
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
