/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_find_target.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:12:04 by tkwak             #+#    #+#             */
/*   Updated: 2024/03/13 11:12:06 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

/*	[F]	
	[Description]
	Find the specific target's existence,
	such as "pipe" or "redirec" or "next_redirec" among the tokens.
	If found, returns an (INDEX) of position of it.

	= 토큰 배열에서 특정 타겟을 찾는 함수
*/
int	find_target_index(int *token, int target, int *i)
{
	int	index;

	index = i[0];
	while (index < i[1])
	{
		if (token[index] == target)
			return (index);
		index++;
	}
	return (-1);
}

/*	[F]
	[Form & Param]
	find_index_pipe(token, i);
		Param(1): Array, saves the type of tokens // W P R S D
		Param(2): Pointer to integer from the function("parse_cmd_line")
					i[0]: 0		// Starting index
					i[1]: 5		// Length of token

	Target = T_PIPE
*/
int	find_index_pipe(int *token, int *i)
{
	return (find_target_index(token, T_PIPE, i));
}

/*	[F]	
	Target = T_REDIREC
*/
int	find_index_redirec(int *token, int *i)
{
	return (find_target_index(token, T_REDIREC, i));
}

/*	[F]	
	Target = T_REDIREC
	
	[Explanation]
	index[2] // Order of point
		index[0]: Start point to find the next Redirection.
			i[0] + 1 // next character in same token.
				ex) >>>

		index[1]: End point to find the next Redirection.
			i[1]	 // next token.
*/
int	find_index_next_redirec(int *token, int *i)
{
	int	index[2];

	index[0] = i[0] + 1;
	index[1] = i[1];
	return (find_target_index(token, T_REDIREC, index));
}

/*	[F]
	Update
*/
void	update_pipe_index(int *i, int pipe_index, int tmp)
{
	i[0] = pipe_index + 1;
	i[1] = tmp;
}
