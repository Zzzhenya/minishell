/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:10:59 by tkwak             #+#    #+#             */
/*   Updated: 2024/02/27 20:43:58 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// [DEFINE MACRO]
# define T_NULL 0
# define T_WORD 1
# define T_PIPE 2
# define T_REDIREC 3
# define T_S_QUOTE 4
# define T_D_QUOTE 5

# define NODE_NULL_HANDLE 0
# define NODE_PIPE 1
# define NODE_CMD 2
# define NODE_SIMPLE_CMD 3
# define NODE_FILE_PATH 4
# define NODE_ARGV 5
# define NODE_REDIRECTS 6
# define NODE_SIMPLE_REDIRECT 7
# define NODE_RED_TYPE 8
# define NODE_FILE_NAME 9

# define REL_TYPE_R 1
# define REL_TYPE_RR 2
# define REL_TYPE_L 3
# define REL_TYPE_LL 4

# define _XOPEN_SOURCE 700

// [HEADER FILE]

// 1. [f] close, read, write, access, dup, dup2, execve, fork, pipe, unlink
// 	  STDIO_FILENO, STDOUT_FILENO, getcwd, chdir, isatty, ttyname, ttyslot
# include <unistd.h>

// 2. [f] malloc, free, exit, getenv
# include <stdlib.h>

// 3. [f] printf, perror
# include <stdio.h>

// 4. [f] open, O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, O_TRUNC
# include <fcntl.h>

// 5. [f] INT_MAX, INT_MIN, UNIT_MAX
# include <limits.h>

// 6. [f] errno, EACCES, ENOENT
# include <errno.h>

// 7. [f] readline
# include <readline/readline.h>

// 8. [f] add_history, clear_history
# include <readline/history.h>

// 9. [f] wait, waitpid, wait3, wait4
# include <sys/wait.h>

// 10. [f] signal, kill, SIGINT, SIGQUIT, sigaction, sigemptyset, sigaddset
# include <signal.h>

// 11. [f] tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <curses.h>

// 12. [f] All the functions from LIBFT
# include "../libft/libft.h"

/* NOT USED
// opendir, readdir, closedir
# include <dirent.h>

// strerror
# include <string.h>

// stat, lstat, fstat
# include <sys/stat.h>

// ioctl
# include <sys/ioctl.h>

// tcsetattr, tcgetattr
# include <termios.h>

// ???
# include <term.h>
*/

// [GLOBAL VARIABLE]
extern int	g_exit_status;

/////////////////////////////////// [STRUCT] ///////////////////////////////////

// Validate input & tokenization
typedef struct s_data
{
	int		n_word;
	int		n_sq;
	int		n_dq;
	char	**token;
	char	*str;
}	t_data;

/*
//
typedef struct s_cmd
{
	struct s_cmd		*left_child;
	struct s_cmd		*right_child;
	char				**cmdstr;
	int					node_type;
	int					pipe_exist;
	int					pre_flag;
}	t_cmd;

//
typedef struct s_stdio
{
	int				re_type;
	char			*filename;
	struct s_stdio	*next_stdio;
}	t_stdio;

//
typedef struct s_envp
{
	char	**envp;
	char	*cd_hist;
}	t_envp;
*/

// [FUNCTIONS]

/* [JASON] */

/* [ INPUT_VALIDATE  & TOKENIZATION ] */

// [ qoute.c ]
int	count_quote(char *str, t_data *data);
int	check_quote_arrangement(char *str, int i);
int	check_unescaped_quote(char *str);
int	check_quote_order(char *user_input, t_data *data, int i, int k);

// [ chopping.c ]
char	*case_s_quote(t_data *data, char *str, int i, int j);
char	*case_d_quote(t_data *data, char *str, int i, int j);
int	check_str_null(t_data *data, char *str, int i, int j);
int	ft_chopper(t_data *data, char *str, int j);

// [ expanding.c ]
int	find_matching_env_row(char *str, char **env);
char		*trim_single_quotes(char *str);
int	remove_single_quotes_from_token(t_data *data, int i);
char		*replace_substring(char *token, char *row_matched_env, int column_index_dollar);
int	expand_env(t_data *data, char **env, int i);

// [ validating.c ]
void	toggle_inword_inquote(int *flag_inword, int *n_word, int *flag_inquote);
int	count_word(const char *str, int n_word, int flag_inword, int flag_inquote);
char	**validate_input(char *user_input, char **env);

//////////////////////////////

/* [ PARSING (TREE) ] */

// [ parsing.c ]
/*
 replace_exit_status
token_data
token_length
syntax_pipe
*/

// [ get_cmds.c ]
t_cmd	*parse_user_input(char *user_input, t_envp *env);

//////////////////////////////

/* [ UTILS ] */

// [ util_skip.c ]
int	ft_isspace(char c);
void	skip_normal_char(char *str, int *i);
void	skip_space_in_str(char *str, int *i);

// [ util_str.c ]
int	ft_strchr_m(char *str, char c);
int	ft_strcmp(char *s1, char *s2)
int	ft_putstr_m(char *str)
int	ft_strcpy_m1(t_data *data, char *str, int len, int j);
int	ft_strcpy_m2(t_data *data, char *str, int len, int j);

// [ util_free.c ]
void	free_2d(char **arr);
void	free_stdios(t_stdio *stdios);
void	free_tree(t_cmd	*tree);
void	freeing_norminette(char **validated_input, int *token);

// [etc.c ]
int	token_length(int *token)

// [ LIBFT ]
/*
ft_strlen
ft_split
ft_strncmp
*/

// [ LIBRARY_MINISHELL ]


///////////////////////////////////////////////////////////////////////////////////////////

/* [ STARTING POINT ] */

// [ main.c ]
char	**save_all_env_paths(char **envp);
char	*get_allocated_cwd(void);
void	interactive_mode(t_cmd **tree, char **envp, t_envp *env);
void	non_interactive_mode(t_cmd **tree, char *input, char **envp, t_envp *env);
int	main(int argc, char **argv, char **envs);

///////////////////////////////////////////////////////////////////////////////////////////

/*
int		if_tmp_null(t_data *data, char *tmp, int i, int k);
int		ft_chopper(t_data *data, char *tmp, int k);
void	else_if_str(int *inquotes, int *count, int *inword);
int		word_counter(const char *str, int count, int inword, int inquotes);
char	**input_validation(char *tmp, char **env);
*/






///////////////////////////////////////////////////////////////////////////////////////////

/* [ SHENYA] */

// [ Executing ]
//search_tree
//wait_each_commands

// [ FORK ]

// [ SIGNAL ]
//set_signals_interactive

// [ BUILD-IN ] 
// 1. CD

// 2. ENV

// 3. PWD

// 4. ECHO

// 5. EXIT

// 6. UNSET

// 7. EXPORT


//////////////////////////////// [MEMO] ////////////////////////////////

// STDIN_FILENO: File descriptor of STDIN, relating with input source like Key-board.
// STDOUT_FILENO: File descriptor of STDIN, relating with input source like Key-board.

#endif
