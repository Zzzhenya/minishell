#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
/* READLINE includes + flags in Makefile */
# include <readline/readline.h>
# include <readline/history.h>
/* execve fork */
# include <unistd.h>
/* wait wait2 wait3*/
#include <sys/wait.h>

char	**ft_splitbyspace(char *str);

#endif