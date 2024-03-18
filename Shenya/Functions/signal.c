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
	signal(SIGINT, sig_handler);
	//ctrl + d -> print exit, exit(1)
	// ctrl + \ -> do nothing
}