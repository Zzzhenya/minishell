/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:29:37 by tkwak             #+#    #+#             */
/*   Updated: 2024/02/27 20:29:39 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_word(const char *str, int n_word,
	int inword, int inquote, t_data data)
{
	char	prev;
	int		cpy_n_sq;
	int		cpy_n_dq;

	prev = 0;
	cpy_n_sq = data.n_sq;
	cpy_n_dq = data.n_dq;
	while (*str)
	{
		if (*str == ' ' && inquote == 0)
			inword = 0;
		else if (*str == '<' && inquote == 0)
		{
			if (*(str + 1) == '<')
			{
				str++;
				if (*(str + 1) != '<')
				{
					n_word++;
					inword = 0;
				}
				else
				{
					g_exit_status = 2;
					printf("Syntax error\n");
					return (0);
				}
			}
			else
			{
				n_word++;
				inword = 0;
			}
		}
		else if (*str == '>' && inquote == 0)
		{
			if (*(str + 1) == '>')
			{
				str++;
				if (*(str + 1) != '>')
				{
					n_word++;
					inword = 0;
				}
				else
				{
					g_exit_status = 2;
					printf("Syntax error\n");
					return (0);
				}
			}
			else
			{
				n_word++;
				inword = 0;
			}
		}
		else if (*str == '|' && inquote == 0)
		{
			n_word++;
			inword = 0;
		}
		else if (*str == '\"' || *str == '\'')
		{
			if (inquote == 1)
			{
				if (prev != *str)
				{
					if (prev == 0)
					{
						prev = *str;
						n_word++;
						inquote = 1;
						inword = 1;
					}
					else
					{
						if (*str == '\'' && prev != '\"')
							cpy_n_sq--;
						else if (*str == '\"' && prev != '\'')
							cpy_n_dq--;
					}
				}
				else
				{
					if (*str == '\"')
					{
						if (*(str + 1) == ' ' && (cpy_n_dq % 2 != 0))
						{
							inword = 0;
							inquote = 0;
							prev = 0;
						}
						else if (ft_isalpha(*(str + 1)))
						{
							if (cpy_n_dq % 2 != 0)
							{
								inquote = 0;
								prev = 0;
							}
							else
							{
								inword = 1;
								inquote = 1;
							}
						}
						if (prev != '\'')
							cpy_n_dq--;
					}
					else
					{
						if (*(str + 1) == ' ' && (cpy_n_sq % 2 != 0))
						{
							inword = 0;
							inquote = 0;
							prev = 0;
						}
						else if (ft_isalpha(*(str + 1)))
						{
							if (cpy_n_sq % 2 != 0)
							{
								inquote = 0;
								prev = 0;
							}
							else
							{
								inword = 1;
								inquote = 1;
							}
						}
						if (prev != '\"')
							cpy_n_sq--;
					}
				}
			}
			else
			{
				prev = *str;
				if (*str == '\'')
				{
					if (inword == 0)
						n_word++;
					cpy_n_sq--;
				}
				else if (*str == '\"')
				{
					if (inword == 0)
						n_word++;
					cpy_n_dq--;
				}
				inquote = 1;
				inword = 1;
			}
		}
		else
		{
			if (inword == 0)
			{
				n_word++;
				inword = 1;
			}
		}
		str++;
	}
	return (n_word);
}

char	*ft_cpy_str(char *dest, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**split_str_by_sq(char *str, int i, int j)
{
	int		start;
	char	**tmp;

	start = 0;
	tmp = (char **)malloc(sizeof(char *) * (100));
	if (tmp == NULL)
		return (NULL);
	while (str[i])
	{
		while (str[i] && str[i] == '\'')
			i++;
		start = i;
		while (str[i] && str[i] != '\'')
			i++;
		if (i > start)
		{
			tmp[j] = (char *)malloc(sizeof(char) * ((i - start) + 1));
			if (tmp[j] == NULL)
				return (NULL);
			ft_cpy_str(tmp[j], &str[start], i - start);
			j++;
		}
	}
	tmp[j] = NULL;
	return (tmp);
}

char	*delete_sq(char *str)
{
	int		i;
	char	*res;
	char	*tmp;
	char	**split_array;

	i = 0;
	res = NULL;
	split_array = split_str_by_sq(str, 0, 0);
	if (split_array == NULL)
		return (NULL);
	while (split_array[i] != NULL)
	{
		if (res == NULL)
			res = strdup(split_array[i]);
		else
		{
			tmp = strdup(res);
			free(res);
			res = ft_strjoin(tmp, split_array[i]);
			free(tmp);
		}
		i++;
	}
	i = 0;
	while (split_array[i] != NULL)
	{
		free(split_array[i]);
		i++;
	}
	free(split_array);
	return (res);
}

char	**split_str_by_dq(char *str, int i, int j)
{
	int		start;
	char	**tmp;

	start = 0;
	tmp = (char **)malloc(sizeof(char *) * (100));
	if (tmp == NULL)
		return (NULL);
	while (str[i])
	{
		while (str[i] && str[i] == '\"')
			i++;
		start = i;
		while (str[i] && str[i] != '\"')
			i++;
		if (i > start)
		{
			tmp[j] = (char *)malloc(sizeof(char) * ((i - start) + 1));
			if (tmp[j] == NULL)
				return (NULL);
			ft_cpy_str(tmp[j], &str[start], i - start);
			j++;
		}
	}
	tmp[j] = NULL;
	return (tmp);
}

void	free_temp_array(char **split_array)
{
	int	j;

	j = 0;
	while (split_array[j] != NULL)
	{
		free(split_array[j]);
		j++;
	}
	free(split_array);
}

void	delete_dq_ext(char *tmp, char *res, char **split_array, int j)
{
	tmp = ft_strdup(res);
	free(res);
	res = ft_strjoin(tmp, split_array[j]);
	free(tmp);
}

char	*delete_dq(char *str, t_data *data, int index_token, char **env)
{
	int		j;
	char	*res;
	char	*tmp;
	char	**split_array;

	res = NULL;
	split_array = split_str_by_dq(str, 0, 0);
	if (split_array == NULL)
		return (NULL);
	j = 0;
	while (split_array[j] != NULL)
	{
		if (expand_token_env_1(data, index_token, split_array) == -1)
			return (NULL);
		else if (expand_token_env_2(data, env, index_token, split_array) == -1)
			return (NULL);
		if (res == NULL)
			res = ft_strdup(split_array[j]);
		else
			delete_dq_ext(tmp, res, split_array, j);
		j++;
	}
	free_temp_array(split_array);
	return (res);
}

char	**validate_input(char *user_input, char **env)
{
	t_data	data;

	data.str = user_input;
	if (count_quote(user_input, &data) == -1)
	{
		printf("Syntax error\n");
		return (NULL);
	}
	data.n_word = count_word(data.str, 0, 0, 0, data);
	if (data.n_word == 0)
		return (NULL);
	data.token = malloc((data.n_word + 1) * sizeof(char *));
	if (data.token == NULL)
		return (NULL);
	if (ft_chopper(&data, data.str, 0) == -1)
		return (NULL);
	if (expand_env(&data, env, 0) == -1)
		return (NULL);
	return (data.token);
}
