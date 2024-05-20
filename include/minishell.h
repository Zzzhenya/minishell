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

/*	[DEFINE MACRO]	*/
/*	[F]
	macro for PATH_MAX for cwd/pwd in case its not defined 
*/
//#ifndef PATH_MAX
# define PATH_MAX 2048
# define PATH "/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin"

/*	[F]
	macro for exit status when command not found
*/
# define EX_CMD_NOT_FOUND 127
# define HEREDOCNAME  ".___tmp__4heredoc"

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

/*	[F]
	4. FOR OPEN SOURCE
*/
# define _XOPEN_SOURCE 700

/*	[F]
	5. Color way
*/
# define RS		"\033[0m"		// RESET
# define C      "\033[1;36m"	// CYAN
# define G      "\033[1;32m"	// GREEN
# define B      "\033[1;34m"	// BLUE
# define P      "\033[1;35m"	// PURPLE
# define RED	"\033[1;31m"	// RED
# define W      "\033[1;37m"	// WHITE
# define Y      "\033[1;33m"	// YELLOW
# define EMP	"\033[30;47;20m"

/*	[HEADER FILE]	*/

/*	[F]
	1. close, read, write, access, dup, dup2, execve, fork, pipe, unlink
	STDIO_FILENO, STDOUT_FILENO, getcwd, chdir, isatty, ttyname, ttyslot
*/
# include <unistd.h>

/*	[F]
	2. malloc, free, exit, getenv
*/
# include <stdlib.h>

/*	[F]
	3. [f] printf, perror
*/
# include <stdio.h>

/*	[F]
	4. [f] open, O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, O_TRUNC
*/
# include <fcntl.h>

/*	[F]
	5. [f] INT_MAX, INT_MIN, UNIT_MAX
*/
# include <limits.h>

/*	[F]
	6. [f] errno, EACCES, ENOENT
*/
# include <errno.h>

/*	[F]
	7. [f] readline
*/
# include <readline/readline.h>

/*	[F]
	8. [f] add_history, clear_history
*/
# include <readline/history.h>

/*	[F]
	9. [f] wait, waitpid, wait3, wait4
*/
# include <sys/wait.h>

/*	[F]
	10. [f] signal, kill, SIGINT, SIGQUIT, sigaction, sigemptyset, sigaddset
*/
# include <signal.h>

/*	[F]
	11. [f] tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
*/
# include <curses.h>

/*	[F]
	12. [f] All the functions from LIBFT
*/
# include "../libft/libft.h"

/*	[F]
	13. [f] used for cd - stat, lstat, fstat
*/
# include <sys/stat.h>

/*	[F]
	14. [f] used in signals to inject a linebreak to the stream
		allows to avoid switching to readline SIGINT definition
*/
# include <sys/ioctl.h>

/*	[GLOBAL VARIABLE]	*/
extern int	g_exit_status;

/*	[STRUCT]  */
/*	[F]
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

/*	[F]
	[Description]
	structure to temporarily store data until heredoc

	token:	token type array
	arr:	token content array
	name:	name of the heredoc instance
*/
typedef struct s_tmp
{
	int		*token;
	char	**arr;
	char	*name;
}	t_tmp;

/* [F]
	[Description]
	For norminette (over 25 lines)
*/
typedef struct s_parse
{
	int			n_word;
	int			inword;
	int			inquote;
	int			cpy_n_sq;
	int			cpy_n_dq;
	char		prev;
}	t_parse;

/* [F]
	[Description]
	structure to store pipestatus array

	pid:		process id
	status:		exit status of the process
*/
typedef struct s_ps
{
	pid_t	pid;
	int		status;
}	t_ps;

/* [F]
	[Description]
	structure to store environment related data 

	envlist:	environmental variables stored in a linked list.
	envarr:		a pointer array of environmental variables. 
				Created before calling execve
	cd_hist:	last directory visited with cd. stored using OLDPWD. Required for cd -
	count:		number of env variables stored in the envlist
	cmds:		number of cmds in the pipeline including redirections
	builtin:	check for when procs == 1 whether the proc is a builtin
	paths:		pointer array to PATH variable split at ':'
	tree:		pointer to the cmd tree
	user_input:	string from readline
	procs:		number of processes in the pipeline
	c:			current process number. used as the index of pipestatus array
	arr:		pipestatus array
*/
typedef struct s_envp
{
	t_list	*envlist;
	char	**envarr;
	char	*cd_hist;
	int		count;
	int		builtin;
	char	**paths;
	t_cmd	*tree;
	char	*user_input;
	int		procs;
	int		c;
	t_ps	*arr;
	int		saved_stdin;
	int		saved_stdout;
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

typedef struct s_expand
{
	int		i_dollar;
	int		row_env;
	int		x;
	int		z;
	int		y;
	int		length;
	char	*res1;
	char	*res;
	char	*tmp;
}	t_expand;

/*	[FUNCTIONS]	 */
// [ lexical_analysis.c ]
int			check_token_length(int *token);
int			check_redirections(char *str);
int			check_token_type(char *str);
int			count_row_2d_array(char **array);
int			*token_malloc(char **after_chopping);

// [ lexical_change_exit_status.c ]
void		if_dollar_q_mark(char **tmp, char *status, int *flag, int *i);
void		if_tmp(int *flag, char *tmp, char **argv);
char		*convert_status_to_ascii(void);
void		replace_exit_status(char ***argv, int i, int flag, int j);

/* [ LEXER ] INPUT_VALIDATE  & TOKENIZATION */
// [ lexical_chopping_tool.c ]
int			check_str_null(t_data *data, char *str, int i, int j);
char		*meet_space_1(t_data *data, char **str, int *i, int *j);
char		*meet_space_2(t_data *data, char **str, int *i, int *j);
char		*case_s_quote(t_data *data, char *str, int i, int j);
char		*case_d_quote(t_data *data, char *str, int i, int j);

// [ lexical_chopping.c ]
void		check_sq(t_data *data, char **str, int *i, int *j);
void		check_dq(t_data *data, char **str, int *i, int *j);
int			ft_chopper(t_data *data, char *str, int j, int i);
char		*dup_array(char **str, char *res);

// [ lexical_expanding_tool.c ] 5
char		**split_str_by_sq(char *str, int i, int j);
char		*delete_sq(char *str);
char		**split_str_by_dq(char *str, int i, int j);
void		delete_dq_ext(char *tmp, char *res, char **split_array, int j);
char		*delete_dq(char *str, char **env);

// [ lexical_expanding_tool2.c ] 3
char		*get_pid_string(void);
void		skip_non_dollar(t_expand *data, char **array_split);
void		skip_non_space_sq(t_expand *data,
				char **array_split, char **env, int *i);

// [ lexical_expanding_tool3.c ] 4
void		init_expand_data_struct(t_expand *data);
void		expand_replace_substr_if1(t_expand *data, char **array_split,
				char **env, int *i);
void		expand_replace_substr_else(t_expand *data,
				char **array_split, char **env, int *i);
void		expand_replace_substr_if(t_expand *data, char **array_split,
				int *i, char **env);

// [ lexical_expanding_tool4.c ] 4
char		*replace_substring_special(t_expand *data, char **env, int len);
char		*replace_substring_1(char *token, char *row_env, int i_dollar);
void		replace_substring_cpy_iter(char *src, int *cpy, int *i, char *dest);
char		*replace_substring(char **array_split, int *i, char **env,
				t_expand *data);
char		*delete_dq_only(char *str);

// [ lexical_expanding.c ]
int			expand_token_env_3(t_data *data, int i);
int			expand_token_env_4(t_data *data, char **env, int i);
int			expand_token_env_5(char **split, int i);
int			expand_token_env_6(char **split, char **env, int i);
int			expand_env(t_data *data, char **env, int i, int j);

// [ lexical_qoute.c ]
int			count_quote(char *str, t_data *data);
char		*extract_quoted_string(char *str, int i);
int			check_quote_arrangement(char *str, int i);
int			check_unescaped_quote(char *str);

// [ lexical_validating_cnt_wd.c]
int			ct_wd_dq(t_parse *checks, const char *str);
int			ct_wd_sq(t_parse *checks, const char *str);
int			ct_wd_outquote(t_parse *checks, const char *str);
int			ct_wd_inquote(t_parse *checks, const char *str);
int			ct_wd_else(t_parse *checks);

// [ lexical_validating_cnt_wd1.c]
int			ct_wd_left_rdr(t_parse *checks, const char *str);
int			ct_wd_right_rdr(t_parse *checks, const char *str);
int			ct_wd_rdr_pipe(t_parse *checks, const char *str);

// [ lexical_validating.c ]
int			count_word(const char *str, t_data data);
char		*ft_cpy_str(char *dest, char *src, int len);
void		free_temp_array(char **split_array);
char		**validate_input(char *user_input, char **env);

/* [ SETTING HEREDOC ]*/
// [ setup_and_run_heredoc.c]
int			setup_and_run_heredoc(int *token, char **arr, t_envp *env);

// [ stage_run_heredoc.c]
int			stage_heredoc(int fd, char *word, t_envp *env, t_tmp *temp);
int			open_run_here(char *word, t_envp *env, t_tmp *temp);

/* [ PASER ]*/
// [ syntax_analysis.c ]
int			syntax_simple_redirect(char **cmd_line, int *i, t_cmd **node);
int			syntax_redirects(char **cmd_line, int *token, int *i, t_cmd **node);
int			syntax_simple_cmd(char **cmd_line,
				int *token, int *i, t_cmd **node);
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
void		free_for_norminette(char **validated_input, int *token);
int			if_token_order_weird(int *tokens, int numTokens, char **input);
int			check_token_order(const int *tokens, int numTokens);
t_cmd		*parse_user_input(char *user_input,
				t_envp *env, t_cmd *cmd_tree, int tmp);

/* [ UTILS ] */
// util_debug.c
int			get_arg_count(char **argv);
void		print_tree(t_cmd *node);
void		print_tree(t_cmd *node);

// [ util_error.c ]
void		syntax_pipe_error_print(void);
char		*delete_space_from_str(char *str);
int			find_matching_env_row(char *str, char **env);

// [ util_free.c ]
void		free_2d(char **arr);
void		free_tree(t_cmd	*tree);
void		free_stdios(t_redirec *stdios);
void		free_arr(char **arr, int loc);

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

/* [ STARTING POINT ] */
// [ main.c ]
void		interactive_mode(t_cmd **tree, t_envp *env,
				char *user_input);
int			main(int argc, char **argv, char **envs);

/* [ ENVIRONMENT ] */
// [setup_env.c]
int			setup_env(t_cmd *tree, t_envp *env);
int			count_procs(t_cmd *tree);
char		**save_all_env_paths(char **envp, t_envp *env);

// [reset_env.c]
void		free_things(t_cmd *tree, t_envp *env,
				char **envp, char *user_input);

// [create_env_list.c]
int			store_envp(t_envp *env, char **envs);

// [extract_env_arr.c]
void		clear_envlist(t_envp *env);
int			extract_envarr(t_envp *my_data);
void		free_string(void *input);

// [init_env.c]
void		init_env(t_envp *env);

/* [ EXECUTING ] */
// [search_tree.c]
void		search_tree(t_cmd *node, t_envp *env);

// [execite_simple_cmd.c]
void		execute_simple_cmd(t_cmd *cmd, t_redirec **stdios, t_envp *env);

// [execute_one_builtin.c]
void		exec_one_builtin_cmd(t_cmd *cmd, t_redirec **stdios,
				t_envp *env, int i);

// [cmd_functions.c]
char		*check_cmd_in_path(char **envp, char *command);
void		print_error_cmd(t_cmd *file_path, char **envp);
void		exec(char **cmd, char **env, t_envp *envo, int i);

// [configure_pipes.c]
void		write_pipefd(int pipefd[2],
				int *initial_input, int flag_pipe_exist);
void		setup_pipe_for_child(int *pipefd,
				int pipe_exist, int initial_input);

// [execute_simple_cmd.c]
void		clean_stdios_list(t_redirec **stdios);

/* [ REDIRECTION ] */
// [setup_redirections.c]
int			setup_redirections(t_redirec *stdios);
void		dup_and_redirect(int oldfd, int newfd);

// [setup_right_redirections.c]
int			setup_rr(t_redirec *stdios);
int			setup_r(t_redirec *stdios);

// [setup_left_redirections.c]
int			setup_ll(t_redirec *stdios);
int			setup_l(t_redirec *stdios);

/* [ ETC ] */
// [here_doc_functions.c]
void		heredoc_input(int fd, char *word, t_envp *env, char *line);

// [ SIGNAL ]
// [signals.c]
void		install_signals_main(int c);
void		install_signals_child(void);

// [heredoc_signal.c]
void		install_signals_here(void);

/* [ BUILT-IN ] */
// [cd.c]
void		exec_cd(char **argv, t_envp *my_data, char *path, int c);
char		*change_to_home(t_envp	*my_data);

// [cd_utils.c]
void		print_cd_error(char *path, char *message);
int			not_a_dir(char	*path);
char		*cd_get_home_path(char *temp);

// [env.c]
void		exec_env(char **argv, t_envp *my_data, int c);

// [pwd.c]
void		exec_pwd(t_envp *my_data, int c);
char		*get_pwd(t_envp *my_data, int c);

// [echo.c]
void		exec_echo(char **argv, int c, char **arr, t_envp *my_data);

// [exit.c]
void		exec_exit(char **argv, t_envp *my_data, int c);

// [exit_utils.c]
void		free_stuff_and_exit(t_envp *my_data, int yes, int i);

// [unset.c]
void		exec_unset(char **argv, t_envp *my_data, int c);
void		unset_one_var(char *var, t_envp *my_data, int c);

// [export.c]
void		exec_export(char **argv, t_envp *my_data, int c);

// [export_utils.c]
void		print_export_error(char *var, char *val, char *message);
int			is_valid_var_start(unsigned char c);
int			is_valid_var_char(char *var);
void		print_variables_list(char **arr);
void		export_one_var(char *str, char *var, t_envp *my_data, int c);

// [builtin_utils.c]
char		**strip_empty_strings(char **cmdstr);
int			count_non_empty_strings(char **cmdstr);
char		**split_at_first_occ(char *str, char c, int loc);

// [redirection_error_handle.c]
int			redirection_error_handle(t_cmd *type, pid_t pid, t_envp *env);

// [child_process.c]
void		pid_zero_exec(t_cmd *cmd, t_envp *env, pid_t pid);

// [wait_blocked_cmds.c]
void		wait_each_command(t_cmd *tree, t_envp *env);
int			count_commands(t_cmd *tree);

// [route_builtins.c]
int			check_builtin(t_cmd *file_path, t_cmd *cmd);
void		builtin_router(t_cmd *cmd, t_envp *env, pid_t pid, int i);

/* readline */
void		rl_replace_line(const char *text, int clear_undo);
void		rl_clear_history(void);

/*
[MEMO]
STDIN_FILENO:
File descriptor of STDIN, relating with input source like Key-board.

STDOUT_FILENO:
File descriptor of STDOUT, relating with output source like Monitor.

[NOT USED]
t_redirec	*find_last(t_redirec *stdios, char c, t_redirec *last);
int error_parsing_exit_2(int *tokens, int numTokens, char **input);
char		*replace_substring(char *token,
				char *row_matched_env, int column_index_dollar,
				int after_space, int index_space);
char		*replace_substring_special(char *token,
				char *row_env, int i_dollar, int after_space, int index_space);
char		*replace_substring(char *token,
				char *row_env, int i_dollar, int after_space, int index_space);
int			expand_env(t_data *data, char **env, int i);
void		builtin_action(t_cmd *builtin, char **cmdline, t_envp *env);
void		pid_pid_builtin_n_set(t_cmd *cmd, t_envp *env, pid_t pid);
void		heredoc_input(int fd, char *word);
*/
#endif
