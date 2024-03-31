#include "../../include/minishell.h"

/*
	signal handler for ctrl + c : SIGINT - Parent
	ctrl + d -> print exit, exit(1) <- from interactive_bash
	main readline loop
*/
void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = sig;
		//ioctl(STDIN_FILENO, TIOCSTI, "\n");		
		//g_exit_status = 130;
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line ("", 0);
		rl_redisplay();
	}
}
/*
	Ignore ctrl + \ : SIGQUIT -> do nothing for
		all processes
	ctrl + c : SIGINT - Child -> behave normally
	ctrl + c : SIGINT - Parent-> behave as mentioned
		in sig_handler
*/

void install_signals(pid_t pid)
{
	signal(SIGQUIT, SIG_IGN);
	if (pid <= 0)
		signal(SIGINT, sig_handler);	
	else
		signal(SIGINT, SIG_IGN); 
}