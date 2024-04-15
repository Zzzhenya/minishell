/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 21:33:24 by sde-silv          #+#    #+#             */
/*   Updated: 2024/04/03 21:33:26 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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


void install_signals_here(void)
{
	struct sigaction	act1;
	struct sigaction	act2;

	ft_bzero(&act1, sizeof(act1));
	ft_bzero(&act2, sizeof(act2));
	act1.sa_handler = SIG_IGN;
	act2.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &act1, NULL);
	sigaction(SIGINT, &act2, NULL);

}
*/
void	heredoc_input(int fd, char *word, t_envp *env)
{
	char	*line;
	char 	**arr;
	int k = 1;
	int i = 0;
	int count = 0;

	//printf("word: %s\n", word);
	line = NULL;
	arr = NULL;
	while (1)
	{
		install_signals_here();
		line = readline(">");
		if (!line || ft_strcmp(line, word) == 0)
		{
			if (line)
			{
				free (line);
				line = NULL;
			}
			else
			{
				printf("bash: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", k, word);
			}
			break;
		}
		if (ft_strcmp(line, word) != 0)
		{
			arr = validate_input(line, env->envarr);
			count = get_arg_count(arr);
		/*if (count == 1)
		{
			if (ft_strcmp(line, word) != 0)
			{
				write(fd, line, ft_strlen(line));
				write(fd, "\n", 1);
			}
		}
		else*/
			i = 0;
			while (i < count)
			{
				write(fd, arr[i], ft_strlen(arr[i]));
				i ++;
			}
			write(fd, "\n", 1);
			free_arr(arr, count);
		}
		k ++;
		free (line);
		line = NULL;
	}
	/*
	char	*line;
	int		i;

	i = 0;
	line = ft_calloc(1, 1);
	while (ft_strcmp(line, word) != 0)
	{
		free(line);
		install_signals_here();
		line = readline("heredoc> ");
		if (!line)
			break;
		if (ft_strcmp(line, word) != 0)
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		i ++;
	}
	if (line)
		free (line);*/
}
