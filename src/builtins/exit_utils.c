/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:33:50 by sde-silv          #+#    #+#             */
/*   Updated: 2024/05/07 18:33:52 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_for_exit(t_envp *my_data)
{
	clear_envlist(my_data);
	if (my_data->cd_hist != NULL)
	{
		free (my_data->cd_hist);
		my_data->cd_hist = NULL;
	}
	if (my_data->envarr)
		free_arr(my_data->envarr, my_data->count);
	if (my_data->paths)
		free_2d(my_data->paths);
	if (my_data->tree)
		free_tree(my_data->tree);
	if (my_data->user_input)
	{
		free(my_data->user_input);
		my_data->user_input = NULL;
	}
	rl_clear_history();
}

void	free_stuff_and_exit(t_envp *my_data, int yes, int i)
{
	if ((my_data->builtin == 1 && my_data->procs == 1) || yes == 1)
	{
		if (yes == 1)
		{
			close(my_data->saved_stdout);
			close(my_data->saved_stdin);
		}
		free_for_exit(my_data);
	}
	if (my_data->builtin == 1 || my_data->procs == 1)
	{
		i = my_data->arr[0].status;
		free (my_data->arr);
		g_exit_status = i;
		exit (g_exit_status);
	}
	else if (i > -1)
	{
		i = my_data->arr[i].status;
		free (my_data->arr);
		g_exit_status = i;
		exit (g_exit_status);
	}
	else
		exit (g_exit_status);
}
