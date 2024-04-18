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

void	free_things(t_cmd **tree, t_envp *env, char **envp, char *user_input)
{
	if (*tree)
		free_tree(*tree);
	if (env->envarr)
		free_arr(env->envarr, get_arg_count(env->envarr));
	if (envp)
		free_2d(envp);
	if (user_input)
		free (user_input);
	env->cmds = 0;
	env->builtin = 0;
}

void	interactive_mode(t_cmd **tree, char **envp, t_envp *env,
					char *user_input)
{
	while (1)
	{
		install_signals_main();
		user_input = readline ("Minishell > ");
		if (!user_input)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (user_input[0] != '\n')
		{
			if (user_input[0] != '\0')
				add_history(user_input);
			if (extract_envarr(env) != 0)
				break ;
			envp = save_all_env_paths(env->envarr);
			*tree = parse_user_input(user_input, env);
			env->cmds = count_commands(*tree);
			search_tree(*tree, envp, env);
			wait_each_command(*tree, env);
		}
		free_things(tree, env, envp, user_input);
	}
}

int	main(int argc, char **argv, char **envs)
{
	t_envp	env;

	init_env(&env);
	if (store_envp(&env, envs) < 0)
		return (1);
	(void)argv;
	if (argc == 1)
	{
		if (isatty(STDIN_FILENO) == 1)
		{
			interactive_mode(&(env.tree), env.paths, &env, env.user_input);
			rl_clear_history();
		}
	}
	clear_envlist(&env);
	if (env.cd_hist != NULL)
	{
		free (env.cd_hist);
		env.cd_hist = NULL;
	}
}
