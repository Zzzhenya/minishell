/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:17:46 by tkwak             #+#    #+#             */
/*   Updated: 2024/03/13 10:17:47 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		g_exit_status = 0;

/*	[F]
	[TIPP]
	Same like with the function,
	that is used in the project, PIPEX.

	[Progress]
	1. Search the string, "PATH=", in offficial 'evn'.
	2. split the array by the standard ':'.
		ex) /usr/local/sbin:/usr/local/bin
			-> (1) /usr/local/sbin
			-> (2) /usr/local/bin
*/
char	**save_all_env_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(&envp[i][ft_strlen("PATH=")], ':'));
		i++;
	}
	perror("save_all_env_paths: ");
	exit(EXIT_FAILURE);
}

/*	[F]
	[Progress]
	1. cwd
		current working directory.Casting only, not yet allocating.
	2. cwd = malloc
		Allocate memory, 1024 (generally set this num)
	3. getcwd
		Save cwd's absolute path to cwd as much as 1024 bytes.
		Return pointer of cwd.
	4. ft_strlen
		Check, where is the EOS (=End of string)
	5. cwd[i] = ' '
		Put the 'SPACE' at the End of the string.
	6. cwd[i + 1] = '\0'
		Attach '\0' for finishing string.
	7. return
		Pointer, which save cwd's absolute path.
*/
char	*get_allocated_cwd(void)
{
	int		i;
	char	*cwd;

	cwd = malloc(1024 * sizeof(char));
	if (cwd == NULL)
		return (NULL);
	getcwd(cwd, 1024);
	i = ft_strlen(cwd);
	cwd[i] = ' ';
	cwd[i + 1] = '\0';
	return (cwd);
}

/*	[ ]
	[Progress]
	1. env->cd_hist
		It might mean cd_histroy, change directory_histroy??
		현재 디렉토리의 환경변수에 저장되어있는 히스토리는 아무것도 가리키고
		있지 않다.왜냐하면 아직까지 실행된 명령어가 없기때문에.
	2. while(1)
		Infinite loop
	?? 3. set_signals_interactive

	4. get_allocated_cwd
		Allocate the memory for the "current working directory"
		and save cwd's address to the pointer "p_cwd".
	5. readline
		Show "cwd's meassage" on the prompt
		(ex: tkwak@c4b11c6:~$)
		&& wait until User write the input in Terminal.
	6. add_history
		If User put something in Terminal as a input,
		save that pointer to input to "user_input".
	7.!user_input
		Save cwd (executed cmd), When you press the arrow key in the shell,
		a list of previously entered commands is displayed in the history.
		사용자가 입력한 명령어를 히스토리에 추가, 이전에 입력한 명령어를
		화살표 키를 사용하여 다시 불러올 수 있다.
	8.parse_user_input
		사용자가 입력한 명령어를 분석하여 트리 형태로 변환.
		프로그램이 이해하고 실행할 수 있는 형태의 명령어 구조로 구성된다.
	?? 9.search_tree
		The command is processed by executing the generated tree.
		생성된 트리를 실행하여 명령어를 처리.
	?? 10. wait_each_commands
		Wait for completion of the executed command.
		Each instruction is executed independently and in order.
	11. free_tree & free
		Don't need anymore, so free.
*/
void	interactive_mode(t_cmd **tree, char **envp, t_envp *env)
{
	char	*user_input;
	char	*p_cwd;

	env->cd_hist = NULL;
	while (1)
	{
		set_signals_interactive(-1);
		p_cwd = get_allocated_cwd();
		user_input = readline(p_cwd);
		add_history(user_input);
		if (!user_input)
			exit(0);
		*tree = parse_user_input(user_input, env);
		search_tree(*tree, envp, env);
		wait_each_commands(*tree);
		free_tree(*tree);
		free(user_input);
		free(p_cwd);
	}
}

/*	[ ]
	[Goal]
	To handle the case where multiple commands are provided
	as a single string separated by semicolons.

	[Progress]
	1. ft_split
		Occasion: "ls -l; echo Hello World; mkdir new_directory"
	2. parse_user_input
		Lexer, Paser // Converts "user_inputs" to tree struct.
	3. serach_tree
		Send the result from analysis with Syntax tree,
		to Final output: cmd_tree
	4. free
		no need anymore.
*/
void	non_interactive_mode(t_cmd **tree,
								char *input, char **envp, t_envp *env)
{
	char	**user_inputs;
	int		i;

	user_inputs = ft_split(input, ';');
	i = 0;
	while (user_inputs[i])
	{
		*tree = parse_user_input(user_inputs[i], env);
		search_tree(*tree, envp, env);
		i++;
		free_tree(*tree);
	}
	free_2d(user_inputs);
}
/*
[example]

	User_inputs: "ls -l; echo Hello World; mkdir new_directory"

	After [ft_split]
		user_inputs[0]: "ls-l"
		user_inputs[1]: "echo Hello World"
		user_inputs[2]: "mkdir new_directory"

	After [parse_user_input]
		(1) lexer: chopping & generate token data

				user_inputs[0]: "ls -l"

								Content			Token
					tree[1]: 	"ls"			T_WORD
					tree[2]: 	"-l"			T_WORD
				
				user_inputs[1]: "echo Hello World"

								Content			Token
					tree[1]: 	"echo"			T_WORD
					tree[2]: 	"Hello"			T_WORD
					tree[3]: 	"World"			T_WORD
				
				user_inputs[2]: "mkdir new_directory"

								Content			Token
					tree[1]: 	"mkdir"			T_WORD
					tree[2]: 	"new_directory"	T_WORD
*/

/*	[ ]
	[Option]
	1. Non_interactive_mode
	2. Interactive_mode

	[Variable]
	1. tree	// Data struct (Casting only)
	2. env	// Enviornment struct

	[Progress]
	1. (void)argv, (void)argc
		When parameters are not used in a function,
		casting them to (void) enhances readability
		by explicitly indicating.
	2. save_all_env_paths
		Save all paths from env to "envp".
	3. argc == 2
		non_interactive_mode.
	3. isatty
		If "STDIN" is now connecting with Terminal,
		interactive_mode.
	4. free_2d
		No more need to use
*/
int	main(int argc, char **argv, char **envs)
{
	t_cmd	*tree;
	t_envp	env;
	char	**paths;

	env.env = envs;
	(void)argv;
	(void)argc;
	paths = save_all_env_paths(envs);
	if (argc == 2)
		non_interactive_mode(&tree, argv[1], paths, &env);
	else if (isatty(STDIN_FILENO))
		interactive_mode(&tree, paths, &env);
	free_2d(paths);
}
/*
	[Q1]
	Why (void)argc??
	= [A]
	  If not making (argc, argv) to the tpye of (void),
	  it pops-up error message with compiling "-werror -wextra" options.

	[Q2]
	Where is "char *cd_hist" used for??
	= [ ]
		typedef struct s_envp
		{
			char	**env;
			char	*cd_hist;
		}	t_envp;

	[Q3]
	Goal of "non_interactive_mode" function?? No idea
	= [ ]
*/
