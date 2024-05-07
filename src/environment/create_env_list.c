/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:01:59 by sde-silv          #+#    #+#             */
/*   Updated: 2024/05/07 18:02:03 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
    increment the SHLVL value for each nested terminal
*/

static char	*increment_shlvl(char *str)
{
	char	*val;
	int		num;
	char	*ret;

	val = NULL;
	ret = NULL;
	num = 0;
	val = ft_strchr(str, '=');
	num = ft_atoi(val + 1);
	ret = ft_itoa(num + 1);
	val = ft_strjoin("SHLVL=", ret);
	free (ret);
	free (str);
	return (val);
}

/*
	Store env variables in a linked list pointed by env->envlist
	Store number of of variables in env->count 
*/
int	store_envp(t_envp *env, char **envs)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (envs[i] != NULL)
	{
		temp = ft_strdup(envs[i]);
		if (!temp)
		{
			clear_envlist(env);
			return (-1);
		}
		if (ft_strncmp(temp, "SHLVL=", 6) == 0)
			temp = increment_shlvl(temp);
		ft_lstadd_back(&env->envlist, ft_lstnew(temp));
		temp = NULL;
		env->count ++;
		i ++;
	}
	return (0);
}
