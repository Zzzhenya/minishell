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
	if (val[1] != '\0')
		num = ft_atoi(val + 1);
	else
		num = ft_atoi("0");
	ret = ft_itoa(num + 1);
	val = ft_strjoin("SHLVL=", ret);
	free (ret);
	free (str);
	return (val);
}

t_list *find_variable(t_envp *env, char *search, int len)
{
	t_list	*current;
	t_list	*var;

	var = NULL;
	current = NULL;
	current = env->envlist;
	while (current != NULL)
	{
		if (ft_strncmp(current->content, search, len) == 0)
		{
			var = current;
			break ;
		}
		current = current->next;
	}
	return (var);
}

/*
	set SHLVL value
		if SHLVL with value increment it
		if SHLVL without value set it to 1
		if not SHLVL add SHLVL=1 to end of list
	set PATH value
*/
void	set_basic_vals(t_envp *env)
{
	t_list	*var;
	char	*path;

	var = NULL;
	path = NULL;
	var = find_variable(env, "SHLVL=", 6);
	if (var)
		var->content = increment_shlvl(var->content);
	else
		ft_lstadd_back(&env->envlist, ft_lstnew(increment_shlvl(ft_strdup("SHLVL="))));
	var = find_variable(env, "PATH=", 5);
	if (!var)
	{
		path = ft_strjoin("PATH=", "/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin");
		ft_lstadd_back(&env->envlist, ft_lstnew(path));
	}
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
		ft_lstadd_back(&env->envlist, ft_lstnew(temp));
		temp = NULL;
		env->count ++;
		i ++;
	}
	set_basic_vals(env);
	return (0);
}
