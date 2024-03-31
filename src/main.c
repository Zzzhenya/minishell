/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:17:46 by tkwak             #+#    #+#             */
/*   Updated: 2024/03/19 16:14:11 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_status = 0;

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
/*
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
*/

void	non_interactive_mode(t_cmd **tree,
								char *input, char **envp, t_envp *env)
{
	char	**user_inputs;
	int		i;

	user_inputs = ft_split(input, ';');
	i = 0;
	extract_envarr(env);
	envp = save_all_env_paths(env->envarr);
	while (user_inputs[i])
	{
		*tree = parse_user_input(user_inputs[i], env);
		search_tree(*tree, envp, env);
		i++;
		free_tree(*tree);
	}
	free_2d(user_inputs);
	free_arr(env->envarr, env->count);
	free_2d(envp);
}

void	interactive_mode(t_cmd **tree, char **envp, t_envp *env)
{
	char	*user_input;

	user_input = NULL;
	while (1)
	{
		install_signals(-1);
		user_input = readline ("Minishell > ");
		if (!user_input)
		{
			g_exit_status = 0;
			printf("exit\n");
			break;
		}
		if (user_input[0] != '\0' || user_input[0] != '\n')
		{
			extract_envarr(env);
			envp = save_all_env_paths(env->envarr);
			add_history(user_input);
			*tree = parse_user_input(user_input, env);
			search_tree(*tree, envp, env);
			wait_each_command(*tree);
			if (*tree)
				free_tree(*tree);
			free_arr(env->envarr, env->count);
			free_2d(envp);
		}
		if (user_input)
		{
			free (user_input);
		}
	}
}

/* Initiate t_envp structure variables to NULL and 0 */
void	init_env(t_envp *env)
{
	env->envarr = NULL;
	env->cd_hist = NULL;
	env->envlist = NULL;
	env->count = 0;
}

/*
void	interactive_bash(t_cmd **tree, char **paths, t_envp *env)
{
	char	user_input[1000];

	install_signals();
	if (extract_envarr(env) < 0)
		return ;
	//Replace these two lines with the radline functions
	fgets(user_input, sizeof(user_input), stdin);
	user_input[strcspn(user_input, "\n")] = 0;
	tree = (t_cmd **)parse_user_input(user_input, env);
	if (tree != NULL)
	{
		printf("Successfully created\n");
		printf("flag	pipe 	type\n");
		search_tree(*tree, paths, env);
	}
	else
		printf("Error: Failed to create command tree.\n");
	if (tree)
		free_tree(*tree);
	(void)paths;
}

*/

int	main(int argc, char **argv, char **envs)
{
	t_cmd	*tree;
	t_envp	env;
	char	**paths;

	paths = NULL;
	init_env(&env);
	if (store_envp(&env, envs) < 0)
		return (1);
	//paths = save_all_env_paths(envs);
	if (argc == 2)
		non_interactive_mode(&tree, argv[1], paths, &env);
	else
	{
		(void)argv;
		if (isatty(STDIN_FILENO) == 1)
			interactive_mode(&tree, paths, &env);
	}
	//free_2d(paths);
	clear_envlist(&env);
	if (env.cd_hist != NULL)
	{
		free (env.cd_hist);
		env.cd_hist = NULL;
	}
}

/*

int	main(int argc, char **argv, char **envs)
{
	t_cmd	*tree;
	t_envp	env;
	char	**paths;

	env.envarr = NULL;
	env.cd_hist = NULL;
	env.envlist = NULL;
	tree = NULL;
	env.count = 0;
	paths = save_all_env_paths(envs);
	if (store_envp(&env, envs) < 0)
		return (1);
	if (argc == 2)
		non_interactive_bash(&tree, paths, &env, argv[1]);
	else
	{
		(void)argv;
		if (isatty(STDIN_FILENO) == 1)
		{
			interactive_bash(&tree, paths, &env);
		}
	}
	if (env.envarr)
		free_arr(env.envarr, env.count);
	clear_envlist(&env);
	free_2d(paths);
	return (0);
}

*/
