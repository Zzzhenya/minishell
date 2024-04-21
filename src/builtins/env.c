/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:38:38 by sde-silv          #+#    #+#             */
/*   Updated: 2024/04/02 20:38:39 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_env(char **argv, t_envp *my_data, int c)
{
	t_list	*lst;

	(void)argv;
	lst = (my_data->envlist);
	while (lst)
	{
		ft_putstr_fd((char *)lst->content, 1);
		ft_putchar_fd('\n', 1);
		lst = lst->next;
	}
	my_data->arr[c].status = 0;
}
