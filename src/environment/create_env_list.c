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
	Check whether all chars in val are digits
	If val is NULL or val is empty string -> return 0
	If val has non-digits -> return 0
	If val has digits but val is outof int range -> return 0

*/
int	ft_isinshlvlrange(char *val)
{
	long long	i;

	i = 0;
	if (!val || val[i] == '\0')
		return (0);
	while (val[i] != '\0')
	{
		if (!ft_isdigit(val[i]))
			break ;
		i ++;
	}
	if (val[i] == '\0')
	{
		i = ft_atoi(val);
		if (i > 998 || i < 1)
			return (0);
		else
			return (1);
	}
	else
		return (0);
}

/*
    Increment the SHLVL value for each nested terminal
	if SHLVL is not available or SHLVL value is empty, set the value to 1
	if SHLVL is available, increse value by 1
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
	if (val[1] != '\0' && ft_isunsignedint(val))
		num = ft_atoi(val + 1);
	else
		num = ft_atoi("0");
	ret = ft_itoa(num + 1);
	val = ft_strjoin("SHLVL=", ret);
	free (ret);
	free (str);
	return (val);
}

/*
	Go through the envlist and find the first string
	that compares with search unpto len letters
	return the found linked list node
	if not found return NULL
*/
t_list	*find_variable(t_envp *env, char *search, int len)
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
		if SHLVL with value increment it and replace
		if not SHLVL add SHLVL=1 to end of list
	set PATH value
		if not PATH add default PATH sting to end of list
*/
void	set_basic_vals(t_envp *env)
{
	t_list	*var;
	char	*str;

	var = NULL;
	str = NULL;
	var = find_variable(env, "SHLVL=", 6);
	if (var)
		var->content = increment_shlvl(var->content);
	else
	{
		str = increment_shlvl(ft_strdup("SHLVL="));
		ft_lstadd_back(&env->envlist, ft_lstnew(str));
	}
	var = find_variable(env, "PATH=", 5);
	if (!var)
	{
		str = ft_strjoin("PATH=", PATH);
		ft_lstadd_back(&env->envlist, ft_lstnew(str));
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
