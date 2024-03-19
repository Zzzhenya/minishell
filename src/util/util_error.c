/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:13:21 by tkwak             #+#    #+#             */
/*   Updated: 2024/03/13 10:13:22 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	syntax_pipe_error_print(void)
{
	write(2, "syntax error near unexpected token '|'\n",
		ft_strlen("syntax error near unexpected token '|'\n"));
	g_exit_status = 1;
}
