/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:03:02 by sde-silv          #+#    #+#             */
/*   Updated: 2024/05/07 18:03:04 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Initiate t_envp structure variables to NULL and 0 */
void	init_env(t_envp *env)
{
	env->envarr = NULL;
	env->cd_hist = NULL;
	env->envlist = NULL;
	env->count = 0;
	env->builtin = 0;
	env->paths = NULL;
	env->tree = NULL;
	env->user_input = NULL;
	env->procs = 0;
	env->c = 0;
	env->arr = NULL;
}
