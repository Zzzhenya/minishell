#include "../../include/minishell.h"

/*	[F]
	Error handling for pipe function.
	
	In write function, first param means "fd".
		fd 0: stdin
		fd 1: stdout
		fd 2: stderr
*/
void	syntax_pipe_error_print(void)
{
	write(2, "syntax error near unexpected token '|'\n",
		ft_strlen("syntax error near unexpected token '|'\n"));
	g_exit_status = 1;
}