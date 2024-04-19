/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:10:59 by tkwak             #+#    #+#             */
/*   Updated: 2024/04/10 16:55:44 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
	[F]
	macro for PATH_MAX for cwd/pwd in case its not defined 
*/
//#ifndef PATH_MAX
# define PATH_MAX 2048

/*
	[F]
	macro for exit status when command not found
*/
# define EX_CMD_NOT_FOUND 127
# define HEREDOCNAME  ".___tmp__4heredoc"

//	[DEFINE MACRO]
/*	[F]
	1. macro for "token"
*/
# define T_NULL 0
# define T_WORD 1
# define T_PIPE 2
# define T_REDIREC 3
# define T_S_QUOTE 4
# define T_D_QUOTE 5

/*	[F]
	2. macro for "tree_node"

	TREE				LEAF
	1. N_CMD
	2. N_SIMPLE_CMD		3. N_FILE_PATH
						4. N_ARGV
	5. N_REDIREC
	6. N_SIMPLE_REDIREC 7. N_REDIREC_TYPE
						8. N_FILE_NAME

	[Description]
	N_CMD: Generating new "CMD" tree struct.
	N_SIMPLE_CMD: Generating new "SIMPLE_CMD" tree struct.
	N_FILE_PAHT: Generating end "FILE_PATH" tree struct.
	N_ARGV: Generating end "ARGV" tree struct.
	N_REDIREC: Generating new "REDIREC" tree struct.
	N_SIMPLE_REDIREC: Generating new "SIMPE_REDIREC" tree struct.
	N_REDIREC_TYPE: Generating end "REDIREC_TYPE" tree struct.
	N_FILE_NAME: Generating end "FILE_NAME" tree struct.

	Every node macro consist of "CMD",
	staring with CMD and dividing with others.
	# define N_PIPE 1: No need, but didn't know that...
*/
# define N_CMD 1
# define N_SIMPLE_CMD 2
# define N_FILE_PATH 3
# define N_ARGV 4
# define N_REDIREC 5
# define N_SIMPLE_REDIREC 6
# define N_REDIREC_TYPE 7
# define N_FILE_NAME 8

/*	[F]
	3. macro for types of "redirection".
*/
# define REDIREC_R 1	// '>'
# define REDIREC_RR 2	// '>>'
# define REDIREC_L 3	// '<'
# define REDIREC_LL 4	// '<<'

// 4. ????
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

/* 13. [f] used for cd - stat
	stat, lstat, fstat
*/
# include <sys/stat.h>
/* 14. [f] used in signals to inject a linebreak to the stream
		allows to avoid switching to readline SIGINT definition
	ioctl
*/
# include <sys/ioctl.h>

/* NOT USED
// opendir, readdir, closedir
# include <dirent.h>

// strerror
# include <string.h>

// lstat, fstat
# include <sys/stat.h>

// tcsetattr, tcgetattr
# include <termios.h>

// ???
# include <term.h>
*/

// [GLOBAL VARIABLE]
extern int	g_exit_status;

// [STRUCT]
/* [F]
	[Description]
	Structure for the validated input & tokenization.

	n_word: The number of words.
	n_sq:	The number of single quotes.
	n_dq:	The number of double quotes.
*/
typedef struct s_data
{
	int		n_word;
	int		n_sq;
	int		n_dq;
	char	**token;
	char	*str;
}	t_data;

/* [F]
	[Description]
	Structure for parse tree of cmds from User.

	[Field]
	l_child:	child node
	r_child:	child node
	**cmdstr:	Only used for the [f]"create_leaf_node".
	node_type:	N_PIPE, N_CMD, N_SIMPLE_CMD, N_ARGV, N_FILE_NAME ...
	pipe_exist:	Check whether it exist or not,
				when exist, return (position).
*/
typedef struct s_cmd
{
	struct s_cmd		*l_child;
	struct s_cmd		*r_child;
	char				**cmdstr;
	int					node_type;
	int					pipe_exist;
	int					pre_flag;
}	t_cmd;

// [STRUCT]
/* [F]
	[Description]
	structure to store envp related data 

	envlist:
	environmental variables stored in a linked list.

	envarr:
	a pointer array of environmental variables. Created before calling execve

	cd_hist:
	last directory visited with cd. Required for cd -

	count:
	number of env variables stored in the envlist
*/

typedef struct s_envp
{
	t_list	*envlist;
	char	**envarr;
	char	*cd_hist;
	int		count;
	int		cmds;
	int		builtin;
	char	**paths;
	t_cmd	*tree;
	char 	*user_input;
}	t_envp;

/*	[F]
	[Field]
	1. redirec_type: Type of redirection.
	2. filename: Pointer to file name(address),
				 which is ridirected by redirection.
				 해당 파일의 경로가 이 변수에 저장된다.
	3. next_redirec: Pointer to the next redirection.
*/
typedef struct s_redirec
{
	int					redirec_type;
	char				*filename;
	struct s_redirec	*next_redirec;
}	t_redirec;

// [FUNCTIONS]
/* [ LEXER ] INPUT_VALIDATE  & TOKENIZATION */
// [ lexical_qoute.c ]
int			count_quote(char *str, t_data *data);
int			check_quote_arrangement(char *str, int i);
int			check_unescaped_quote(char *str);
int			check_quote_order(char *user_input, t_data *data, int i, int k);

// [ lexical_chopping.c ]
char		*case_s_quote(t_data *data, char *str, int i, int j);
char		*case_d_quote(t_data *data, char *str, int i, int j);
int			check_str_null(t_data *data, char *str, int i, int j);
int			ft_chopper(t_data *data, char *str, int j);
char		*get_pid_string(void);

// [ lexical_expanding.c ]
char		*replace_substring(char *token,
				char *row_matched_env, int column_index_dollar);
int			expand_token_env_1(t_data *data, int i);
int			expand_token_env_2(t_data *data, char **env, int i);
int			expand_env(t_data *data, char **env, int i);

// [ lexical_validating.c ]
void		toggle_inword_inquote(int *flag_inword,
				int *n_word, int *flag_inquote);
int			count_word(const char *str,
				int n_word, int flag_inword, int flag_inquote);
char		**validate_input(char *user_input, char **env);

// [ lexical_analysis.c ]
int			check_token_length(int *token);
int			check_redirections(char *str);
int			check_token_type(char *str);
int			count_row_2d_array(char **array);
int			*token_malloc(char **after_chopping);

// [ change_exit_status.c ] //
void		if_dollar_q_mark(char **tmp, char *status, int *flag, int *i);
void		if_tmp(int *flag, char *tmp, char **argv);
char		*convert_status_to_ascii(void);
void		replace_exit_status(char ***argv, int i, int flag, int j);

/* [ PASER ]*/
// [ syntax_analysis.c ]
int			syntax_simple_cmd(char **cmd_line,
				int *token, int *i, t_cmd **node);
int			syntax_simple_redirect(char **cmd_line, int *i, t_cmd **node);
int			syntax_redirects(char **cmd_line, int *token, int *i, t_cmd **node);
int			syntax_cmds(char **cmd_line, int *token, int *i, t_cmd **node);
int			syntax_pipe(char **cmd_line, int *token, int *i, t_cmd **node);

// [ syntax_create_node.c ]
t_cmd		*create_tree_node(int type, int pipe_index);
char		**copy_substring_range(char **cmd_line, int start, int end);
t_cmd		*create_leaf_node(char **cmd_line, int type, int start, int end);

// [ syntax_find_target.c ]
int			find_target_index(int *token, int target, int *i);
int			find_index_pipe(int *token, int *i);
int			find_index_redirec(int *token, int *i);
int			find_index_next_redirec(int *token, int *i);
void		update_pipe_index(int *i, int pipe_index, int tmp);

// [ get_cmds.c ]
t_cmd		*parse_user_input(char *user_input, t_envp *env);

/* [ UTILS ] */
// [ util_skip.c ]
int			ft_isspace(char c);
void		skip_normal_char(char *str, int *i);
void		skip_space_in_str(char *str, int *i);
char		*strjoin_c(char *str, char c);
char		*strrjoin(char *s1, char *s2);

// [ util_str.c ]
int			ft_strchr_m(char *str, char c);
int			ft_strcmp(char *s1, char *s2);
int			ft_putstr_m(char *str);
int			ft_strcpy(t_data *data, char *tmp, int len, int k);

// [ util_str2.c ]
char		*strjoin_c(char *str, char c);
char		*strrjoin(char *s1, char *s2);

// [ util_error.c ]
void		syntax_pipe_error_print(void);
char		*delete_space_from_str(char *str);
int			find_matching_env_row(char *str, char **env);
char		*trim_single_quotes(char *str);
int			remove_single_quotes_from_token(t_data *data, int i);

// [ util_free.c ]
void		free_2d(char **arr);
void		free_stdios(t_redirec *stdios);
void		free_tree(t_cmd	*tree);
void		freeing_norminette(char **validated_input, int *token);
void		free_arr(char **arr, int loc);

/* [ STARTING POINT ] */
// [ main.c ]
char		**save_all_env_paths(char **envp);
char		*get_allocated_cwd(void);
void		interactive_mode(t_cmd **tree, char **envp, t_envp *env,
				char *user_input);
void		non_interactive_mode(t_cmd **tree,
				char *input, char **envp, t_envp *env);
int			main(int argc, char **argv, char **envs);
void	free_things(t_cmd **tree, t_envp *env, char **envp, char *user_input);

/* [ ENV ] */
// [ envp_actions.c ]
int			store_envp(t_envp *env, char **envs);
void		clear_envlist(t_envp *env);
int			extract_envarr(t_envp *my_data);
void		free_string(void *input);
void		init_env(t_envp *env);

// [ Executing ]
/*
	search_tree
	wait_each_commands
*/
// [cmd_functions.c]
char		*check_cmd_in_path(char **envp, char *command);
void		print_error_cmd(t_cmd *file_path, char **envp);
void		exec(char **cmd, char **env, t_envp *envo);
// [search_tree.c]
void		search_tree(t_cmd *node, char **envp, t_envp *env);

// [ REDIRECTIONS ]
// [setup_redirections.c]
//void		setup_redirections(t_redirec *stdios);
void		setup_redirections(t_redirec *stdios, t_envp *env);

// [ETC ]
t_redirec	*find_last(t_redirec *stdios, char c, t_redirec *last);

// [here_doc_functions.c]
//void		heredoc_input(int fd, char *word);
void		heredoc_input(int fd, char *word, t_envp *env);

// util_debug.c
void		print_tree(t_cmd *node);
int			get_arg_count(char **argv);

// [ SIGNAL ]
// [signals.c]
void		install_signals_main(void);
void		install_signals_hang(void);
void		install_signals_child(void);
void		install_signals_here(void);

// [ BUILT-IN ] 
// [cd.c]
void		exec_cd(char **argv, t_envp *my_data, char *path);

// [env.c]
void		exec_env(char **argv, t_envp *my_data);

// [pwd.c]
void		exec_pwd(void);
char		*get_pwd(void);

// [echo.c]
void		exec_echo(char **argv, int count, char **arr);

// [exit.c]
void		exec_exit(char **argv, t_envp *my_data);
void		free_stuff_and_exit(t_envp *my_data, int yes);

// [unset.c]
void		exec_unset(char **argv, t_envp *my_data);
void		unset_one_var(char *var, t_envp *my_data);

// [export.c]
void		exec_export(char **argv, t_envp *my_data);

// [export_utils.c]
void		print_export_error(char *var, char *val, char *message);
int			is_valid_var_start(unsigned char c);
int			is_valid_var_char(char *var);
void		print_variables_list(char **arr);
//void		export_one_var(char **arr, t_envp *my_data);
void	export_one_var(char *str,char *var, t_envp *my_data);

// [builtin_utils.c]
char		**strip_empty_strings(char **cmdstr);
int			count_non_empty_strings(char **cmdstr);
char		**split_at_first_occ(char *str, char c, int loc);

// [MEMO]
/*
STDIN_FILENO:
File descriptor of STDIN, relating with input source like Key-board.

STDOUT_FILENO:
File descriptor of STDOUT, relating with output source like Monitor.
*/

// [redirection_error_handle.c]
int			redirection_error_handle(t_cmd *type, pid_t pid);

// [child_process.c]
void		pid_zero_exec(t_cmd *cmd, char **envp, t_envp *env, pid_t pid);

// [wait_blocked_cmds.c]
void		wait_each_command(t_cmd *tree, t_envp *env);
int			count_commands(t_cmd *tree);

// [route_builtins.c]
//void		builtin_action(t_cmd *builtin, char **cmdline, t_envp *env);
int			check_builtin(t_cmd *file_path);
//void		pid_pid_builtin_n_set(t_cmd *cmd, t_envp *env, pid_t pid);
void		builtin_router(t_cmd *cmd, t_envp *env, pid_t pid);

/* readline */
void		rl_replace_line(const char *text, int clear_undo);
void		rl_clear_history (void);
void		execute_simple_cmd(t_cmd *cmd, t_redirec **stdios,
				char **envp, t_envp *env);
#endif
