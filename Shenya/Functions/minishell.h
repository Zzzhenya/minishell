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

# include <sys/ioctl.h>

# include "libft/libft.h"

# include <signal.h>

#ifndef PATH_MAX
# define PATH_MAX 2048
#endif

# define EX_CMD_NOT_FOUND 127

typedef struct s_envp
{
	//char	**envp;
	t_list	*envlist;
	char	**envarr;
	char	*cd_hist;
	int		count;
}	t_envp;

/*
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;*/

extern int	g_exit_status;	

char	**ft_splitbyspace(char *str);

int get_arg_count(char **argv);

void	get_env_var(char *name);

int run_command(char **argv);

int run_command1(char *cmd, char **argv, char **envp);

void clean_argv(char **argv, int argc);

/* readline */
void rl_replace_line(const char *text, int clear_undo);

/* envp_actions.c */
int store_envp(t_envp *vars, char **envp);
void free_arr(char **env, int len);
void clear_envlist(t_envp *my_data);
int extract_envarr(t_envp *my_data);
void free_string(void	*input);


/* Built-ins*/
//void	exec_builtin(char **argv);
void	exec_builtin(char **argv, t_envp *my_data);

/* builtins/pwd.c */
void	exec_pwd(void);
char	*get_pwd(void);

/* builtins/cd.c */
//void    exec_cd(char **argv);
void    exec_cd(char **argv, t_envp *mydata);

/* builtins/env.c */
void	exec_env(char **argv, t_envp *my_data);

/* builtins/echo.c */
void	exec_echo(char **argv);

/* builtins/export.c */
void    exec_export(char **argv, t_envp *my_data);

/* builtins/unset.c */
void    exec_unset(char **argv, t_envp *my_data);
void 	unset_one_var(char *var, t_envp *my_data);

/* builtins/exit.c */
void	exec_exit(char **argv, t_envp *my_data);

/* signals.c */
void install_signals(void);
void	sig_handler(int sig);

#endif