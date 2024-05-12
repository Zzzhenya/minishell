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

static void	print_here_error(int k, char *word)
{
	ft_putstr_fd("bash: warning: here-document at line ", 2);
	ft_putnbr_fd(k, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(word, 2);
	ft_putstr_fd("\')\n", 2);
}
/*
static void	print_here_text(int fd, t_envp *env, char *line)
{
	int		count;
	char	**arr;
	int		i;

	count = 0;
	arr = NULL;
	arr = validate_input(line, env->envarr);
	count = get_arg_count(arr);
	i = 0;
	while (i < count)
	{
		write(fd, arr[i], ft_strlen(arr[i]));
		i ++;
	}
	write(fd, "\n", 1);
	free_arr(arr, count);
}*/

static void free_line(char *line)
{
	if (line)
	{
		free (line);
		line = NULL;
	}
}

void	heredoc_input(int fd, char *word, t_envp *env, char *line)
{
	int		k;

	k = 1;
	(void)env;
	g_exit_status = 0;
	install_signals_here();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_here_error(k, word);
			break ;
		}
		if (g_exit_status != 0 && line[0] == '\n')
		{
			if (line)
				free (line);
			break;
		}
		if (line)
		{
			if (ft_strcmp(line, word) == 0)
			{
				free_line(line);
				break ;
			}
			if (ft_strcmp(line, word) != 0)
				ft_putendl_fd(line, fd);
			k ++;
			free (line);
			line = NULL;
		}
	}
}
