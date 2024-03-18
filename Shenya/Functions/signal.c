#include "minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT) // ctrl + c  -> new line
	{
		g_exit_status = sig;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line ("", 0);
		rl_on_new_line();
	}
	//ctrl + d -> print exit, exit(1)
	// ctrl + \ -> do nothing
}

void install_signals(void)
{
	if (signal(SIGINT, sig_handler)!= 0)
		printf("SIGNALS NOT WORKING\n");
	if (signal(SIGQUIT, SIG_IGN)!= 0)
		printf("SIGNALS NOT WORKING\n");
	//ctrl + d -> print exit, exit(1)
	// ctrl + \ -> do nothing
}