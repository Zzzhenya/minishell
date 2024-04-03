#include "../../include/minishell.h"

/*
	make a line  of char size of 1
	continue while the line doesn't have/ is not equal to the delimiter word
		free line
		readline into line
		if readline returns a null line; exit
		check whether the line has delimeter word
			if line desn't have the delimiter;
			write line to fd;
			write line break to fd
		increment i??
	When exiting the while loop free line
*/

void	heredoc_input(int fd, char *word)
{
	char	*line;
	int		i;

	i = 0;
	line = ft_calloc(1, 1);
	while (ft_strcmp(line, word) != 0)
	{
		free(line);
		line = readline("heredoc> ");
		if (!line)
			exit(1);
		if (ft_strcmp(line, word) != 0)
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		i ++;
	}
	free (line);
}
