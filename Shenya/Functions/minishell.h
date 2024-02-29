#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
/* READLINE includes + flags in Makefile */
# include <readline/readline.h>
# include <readline/history.h>
/* execve fork chdir getcwd*/
# include <unistd.h>
/* wait wait2 wait3*/
# include <sys/wait.h>
#if __linux__ 
# include <sys/errno.h>
#else
# include <errno.h>
#endif
# include <limits.h>
# include "libft/libft.h"

#ifndef PATH_MAX
# define PATH_MAX 2048
#endif

# define EX_CMD_NOT_FOUND 127

extern int	g_exit_status;

char	**ft_splitbyspace(char *str);

int get_arg_count(char **argv);

void	get_env_var(char *name);

int run_command(char **argv);

int run_command1(char *cmd, char **argv);

void clean_argv(char **argv, int argc);

/* Built-ins*/
void	exec_builtin(char **argv);

/* builtins/pwd.c */
void	exec_pwd(void);

/* builtins/cd.c */
void    exec_cd(char **argv);

#endif