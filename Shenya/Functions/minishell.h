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
# include <sys/wait.h>

#if __linux__ 
# include <sys/errno.h>
#else
# include <errno.h>
#endif

# include "libft/libft.h"

char	**ft_splitbyspace(char *str);

int get_arg_count(char **argv);

void	get_env_var(char *name);

int run_command(char **argv);

int run_command1(char *cmd, char **argv);

void clean_argv(char **argv, int argc);

#endif