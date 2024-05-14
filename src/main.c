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

/*
void	non_interactive_mode(t_cmd **tree,
								char *input, char **envp, t_envp *env)
{
	char	**user_inputs;
	int		i;

	user_inputs = ft_split(input, ';');
	i = 0;
	extract_envarr(env);
	envp = save_all_env_paths(env->envarr, env);
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
}*/

void	interactive_mode(t_cmd **tree, t_envp *env,
					char *user_input)
{
	while (1)
	{
		install_signals_main(10);
		user_input = readline ("minishell$ ");
		if (!user_input)
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		if (user_input[0] != '\n')
		{
			if (user_input[0] != '\0')
				add_history(user_input);
			if (extract_envarr(env) != 0)
				break ;
			env->paths = save_all_env_paths(env->envarr, env);
			*tree = parse_user_input(user_input, env);
			// /* memo */
			// printf(C"[3] Executing starts\n\n"RS);
			// /* memo */
			if (*tree != NULL)
			{
				// /* memo */
				// printf("pre_flag  pipe_exist  cmdstr\n");
				// print_tree(*tree);
				// printf("\n-------------------------------------------------------\n\n");
				// /* memo */
				if (setup_env(*tree, env)!= 0)
					break;
				search_tree(*tree, env);
				wait_each_command(*tree, env);
			}
		}
		free_things(*tree, env, env->paths, user_input);
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
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		{
			interactive_mode(&(env.tree), &env, env.user_input);
			rl_clear_history();
		}
	}
	clear_envlist(&env);
	if (env.cd_hist != NULL)
	{
		free (env.cd_hist);
		env.cd_hist = NULL;
	}
	return (g_exit_status);
}
