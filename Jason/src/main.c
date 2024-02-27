#include "../include/minishell.h"

int		g_exit_status = 0;

/*	[F]
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
*/
char	*get_allocated_cwd(void)
{
	int		i;				// index
	char	*cwd;			// current working directory // Casting only, not yet allocating.

	cwd = malloc(1024 * sizeof(char));	// Allocate memory, 1024 (generally set this num)
	if (cwd == NULL)
		return (NULL);
	getcwd(cwd, 1024);					// Save cwd's absolute path to cwd as much as 1024 bytes. Return pointer of cwd.
	i = ft_strlen(cwd);					// Check, where is the EOS (=End of string)
	cwd[i] = ' ';						// Put the 'SPACE' at the End of the string.
	cwd[i + 1] = '\0';					// Attach '\0' for finishing string.
	return (cwd);						// Pointer, which save cwd's absolute path.
}

void	interactive_mode(t_cmd **tree, char **envp, t_envp *env)
{
	char	*user_input;
	char	*p_cwd;
											// It might mean cd_histroy // change directory_histroy??
	env->cd_hist = NULL;					// 현재 디렉토리의 환경변수에 저장되어있는 히스토리는 아무것도 가리키고 있지 않다. 왜냐하면 아직까지 실행된 명령어가 없기때문에.
	while (1)								// Infinite loop
	{
		set_signals_interactive(-1);		// 
		p_cwd = get_allocated_cwd();		// Allocate the memory for the "current working directory" and save cwd's address to the pointer "p_cwd".
		user_input = readline(p_cwd);		// Show "cwd's meassage" on the prompt (ex: tkwak@c4b11c6:~$) && wait until User write the input in Terminal.
		add_history(user_input);			// If User put something in Terminal as a input, save that pointer to input to "user_input".
		if (!user_input)					// Save cwd (executed cmd), When you press the arrow key in the shell, a list of previously entered commands is displayed in the history.
			exit(0);						// 사용자가 입력한 명령어를 히스토리에 추가, 이전에 입력한 명령어를 화살표 키를 사용하여 다시 불러올 수 있다.
		*tree = parse_user_input(user_input, env);	// 사용자가 입력한 명령어를 분석하여 트리 형태로 변환. 프로그램이 이해하고 실행할 수 있는 형태의 명령어 구조로 구성된다.
		search_tree(*tree, envp, env);		// 생성된 트리를 실행하여 명령어를 처리 // The command is processed by executing the generated tree.
		wait_each_commands(*tree);			// Wait for completion of the executed command. Each instruction is executed independently and in order.
		free_tree(*tree);					// Don't need anymore.
		free(user_input);					// Don't need anymore.
		free(p_cwd);							// Don't need anymore.
	}
}

void	non_interactive_mode(t_cmd **tree, char *input, char **envp, t_envp *env)
{
	char	**user_inputs;
	int		i;

	user_inputs = ft_split(input, ';');			// Occasion: "ls -l; echo Hello World; mkdir new_directory"
	i = 0;										// Goal: To handle the case where multiple commands are provided as a single string separated by semicolons.
	while (user_inputs[i])
	{
		*tree = parse_user_input(user_inputs[i], env);	// Lexer, Paser // Converts "user_inputs" to tree struct.
		search_tree(*tree, envp, env);					// Analysis with Syntax tree -> Final output: cmd_tree
		i++;
		free_tree(*tree);								// No more useful -> Free
	}
	free_2d(user_inputs);								// No more useful -> Free
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

/* 
[Option]
	(1): Non_interactive_mode
	(2): Interactive_mode
*/
int	main(int argc, char **argv, char **envs)
{
	t_cmd	*tree;						// Data struct (Casting only)
	t_envp	env;						// Enviornment struct
	char	**paths;

	env.env = envs;
	(void)argv;
	(void)argc;							// When parameters are not used in a function, casting them to (void) enhances readability by explicitly indicating
	paths = save_all_env_paths(envs);	// Save all paths from env to "envp".
	if (argc == 2)						// ac: 2
		non_interactive_mode(&tree, argv[1], paths, &env);
	else if (isatty(STDIN_FILENO))		// If "STDIN" is now connecting with Terminal
		interactive_mode(&tree, paths, &env);
	free_2d(paths);						// No more need to use
}
/*
// [Q1]
//	Why (void)argc??
//	= If not making (argc, argv) to the tpye of (void),
//	  it pops-up error message with compiling "-werror -wextra" options.
//
// [Q2]
//	Where is "char *cd_hist" used for?? NO idea
//
// 		typedef struct s_envp
//		{
//			char	**env;
//			char	*cd_hist;
//		}	t_envp;
//
// [Q3]
//	Goal of "non_interactive_mode" function?? No idea
//
*/





/* [Original code]
void	interactive_mode(t_cmd **tree, char **envp, t_envp *env)
{
	char	*tmp;
	char	*cwd;

	env->cd_hist = NULL;
	while (1)
	{
		set_signals_interactive(-1);
		cwd = print_prompt();
		tmp = readline(cwd);
		add_history(tmp);
		if (!tmp)
			exit(0);
		*tree = parse_user_input(tmp, env);
		search_tree(*tree, envp, env);
		write(1, "\0", 1);
		wait_each_commands(*tree);
		free_tree(*tree);
		free(tmp);
		free(cwd);
	}
}

void	non_interactive_mode(t_cmd **tree, char *input, char **envp, t_envp *env)
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

int	main(int argc, char **argv, char **envs)
{
	t_cmd	*tree;
	t_envp	env;
	char	**paths;

	env.env = envs;
	(void)argc;
	paths = save_all_env_paths(envs);
	if (argc == 2)
		non_interactive_mode(&tree, argv[1], paths, &env);
	else if (isatty(STDIN_FILENO))
		interactive_mode(&tree, paths, &env);
	free_2d(paths);
}
*/
