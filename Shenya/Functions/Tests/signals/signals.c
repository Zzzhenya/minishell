#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/ioctl.h>

void rl_replace_line(const char *text, int clear_undo);

int		g_exit_status = 0;

void sig_handler(int sig)
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
	return;
}

void install_signals(void)
{
	signal(SIGINT, sig_handler);
}

int main (void)
{
	char *line;

	line = NULL;
	install_signals();
	while (1)
	{
		line = readline ("Minishell > ");
		if (line)
			add_history(line);
		free (line);
	}
	return (0);
}