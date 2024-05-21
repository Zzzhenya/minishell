/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_expanding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:12:50 by tkwak             #+#    #+#             */
/*   Updated: 2024/05/18 10:45:14 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	expand_token_env_3(t_data *data, int i)
{
	int	i_dollar;

	i_dollar = ft_strchr_m(data->token[i], '$');
	if (i_dollar != -1 && data->token[i][i_dollar + 1] == '$')
	{
		data->token[i] = get_pid_string();
		if (data->token[i] == NULL)
			return (-1);
	}
	return (0);
}

int	expand_token_env_4(t_data *data, char **env, int i)
{
	int	i_dollar;
	int	row_env;

	i_dollar = ft_strchr_m(data->token[i], '$');
	if (i_dollar != -1 && data->token[i][i_dollar + 1] == '\0')
		return (0);
	else if (i_dollar != -1
		&& (ft_strchr_m(data->token[i], '\'') == -1)
		&& data->token[i][i_dollar + 1] != '?'
		&& data->token[i][i_dollar + 1] != '$')
	{
		row_env = find_matching_env_row(data->token[i] + i_dollar + 1, env);
		if (row_env == -1)
			data->token[i]
				= replace_substring_1(data->token[i], "", i_dollar);
		else
			data->token[i]
				= replace_substring_1(data->token[i], env[row_env], i_dollar);
		if (data->token[i] == NULL)
			return (-1);
	}
	return (0);
}

int	expand_token_env_5(char **split, int i)
{
	int	i_dollar;

	i_dollar = ft_strchr_m(split[i], '$');
	if (i_dollar != -1 && split[i] != NULL
		&& split[i][i_dollar + 1] != '\0' && split[i][i_dollar + 1] == '$')
	{
		split[i] = get_pid_string();
		if (split[i] == NULL)
			return (-1);
	}
	return (0);
}

int	expand_token_env_6(char **split, char **env, int i)
{
	int	i_dollar;
	int	row_env;

	i_dollar = ft_strchr_m(split[i], '$');
	if (i_dollar != -1 && split[i] != NULL && split[i][i_dollar + 1] == '\0')
		return (0);
	else if (i_dollar != -1
		&& split[i] != NULL
		&& split[i][i_dollar + 1] != '?'
		&& split[i][i_dollar + 1] != '$')
	{
		row_env = find_matching_env_row((split[i]) + i_dollar + 1, env);
		if (row_env == -1)
			split[i]
				= replace_substring_1(split[i], "", i_dollar);
		else
			split[i]
				= replace_substring_1(split[i], env[row_env], i_dollar);
		if (split[i] == NULL)
			return (-1);
	}
	return (0);
}

/*	[ TEST ]

	   STR					P/F			RESULT
	----------------------------------------------------
	  $HOME					[O]			/home/tkwak

	 '$HOME'				[O]			 $HOME
	''$HOME''				[O]			 $HOME

	' $HOME 'a				[O]		   | $HOME |a
	'"$HOME"'				[O]			"$HOME"

	 "$HOME"				[O]			/home/tkwak				
	""$HOME""				[O]			/home/tkwak

	" $HOME "a				[O]		 	| /home/tkwak a|

	"a' '$HOME' 'a"			[O]			a' '/home/tkwak' 'a
	"'$HOME'"				[O]			'/home/tkwak'
	'' $HOME ''a			[O]			| /home/tkwak a|

	echo ""''"" | cat -e	[O]			$
	echo ''""'' | cat -e	[O]			$

	[ Problem ]
	echo "a' "$HOME" 'a"
*/
int	expand_env(t_data *data, char **env, int i, int j)
{
	while (data->token[i] != NULL)
	{
		j = 0;
		while (data->token[i][j] != '\0')
		{
			if (data->token[i][j] == '\'' || data->token[i][j] == '\"')
			{
				if (delete_sq_norm(data, env, i, j) == 0)
					break ;
			}
			else
			{
				if (expand_token_env_3(data, i) == -1
					|| expand_token_env_4(data, env, i) == -1)
					return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
