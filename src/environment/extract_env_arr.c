/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_env_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:02:52 by sde-silv          #+#    #+#             */
/*   Updated: 2024/05/07 18:02:54 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 
	Clear the content of the envlist node
*/
void	free_string(void *input)
{
	char	*str;

	str = (char *)input;
	free (str);
	str = NULL;
}

/*
	Clear entire envlist
*/
void	clear_envlist(t_envp *env)
{
	ft_lstclear(&env->envlist, free_string);
}

/*
	extract env variables from the linked list and store in envarr array
*/
int	extract_envarr(t_envp *env)
{
	t_list	*current;
	int		i;
	int		len;

	i = 0;
	len = 0;
	current = NULL;
	current = env->envlist;
	len = ft_lstsize(current);
	env->envarr = (char **)malloc(sizeof(char *) * (len + 1));
	if (!env->envarr)
		return (-1);
	env->envarr[len] = NULL;
	while (current != NULL)
	{
		env->envarr[i] = ft_strdup((char *)current->content);
		if (!env->envarr[i])
		{
			free_arr(env->envarr, i);
			return (-1);
		}
		current = current->next;
		i ++;
	}
	return (0);
}
