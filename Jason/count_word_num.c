#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

void	toggle_inword_inquote(int *flag_inword, int *n_word, int *flag_inquote)
{
	if (*flag_inquote == 1)
	{
		*n_word += 1;
		*flag_inword = 0;
		*flag_inquote = 0;
	}
	else
	{
		*flag_inword = 1;
		*flag_inquote = 1;
	}
	return ;
}

int	count_word_num(const char *str, int n_word, int flag_inword, int flag_inquote)
{
	while (*str)
	{
		if (*str == ' ' && flag_inquote == 0)
			flag_inword = 0;
		else if (*str == '=' || *str == '<' || *str == '>'
			|| *str == '|' || *str == '$')
		{
			n_word++;
			flag_inword = 0;
		}
		else if (*str == '"' || *str == '\'')
			toggle_inword_inquote(&flag_inword, &n_word, &flag_inquote);
		else
		{
			if (flag_inword == 0)
			{
				n_word++;
				flag_inword = 1;
			}
		}
		str++;
	}
	return (n_word);
}

int	main(int ac, char **av)
{
	int	i = 0;
	int	count_words = 0;
	
	if (ac == 2)
	{
		count_words = count_word_num(av[1], 0, 0, 0);
		printf("count_words: %d\n", count_words);
		while (av[1][i])
		{
			printf("av[1][%d]: %c\n", i, av[1][i]);
			i++;
		}
	}
	return (0);
}
