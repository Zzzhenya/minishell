#include "minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT) // ctrl + c  -> new line
	{
		g_exit_status = sig;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line ("", 1);
		rl_on_new_line();
	}
	//ctrl + d -> print exit, exit(1)
	// ctrl + \ -> do nothing
}

int install_signals(void)
{
	signal(SIGINT, sig_handler);
	//ctrl + d -> print exit, exit(1)
	// ctrl + \ -> do nothing
	return (0);
}