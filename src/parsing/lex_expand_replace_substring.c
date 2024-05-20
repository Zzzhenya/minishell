#include "../../include/minishell.h"

/* data->tmp = replace_substring_special(data->res, env[data->row_env],
		// 	       data->i_dollar, data->z, data->y);

// char	*replace_substring_special(char *token,
// 	char *row_env, int i_dollar, int after_space, int index_space)*/
char	*replace_substring_special(t_expand *data, char **env, int len)
{
	int		i;
	int		i_new;
	char	*res;

	i = 0;
	i_new = ft_strchr_m(env[data->row_env], '=') + 1;
	len = (ft_strlen(env[data->row_env] + i_new));
	res = malloc((len + data->i_dollar + 1 + data->z) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (env[data->row_env][i_new] != '\0')
	{
		res[i] = env[data->row_env][i_new];
		i++;
		i_new++;
	}
	while (data->res[data->y] != '\0')
	{
		res[i] = data->res[data->y];
		data->y++;
		i++;
	}
	res[i] = '\0';
	free(data->res);
	return (res);
}

int	cpy_until_dollar(char *res, int *i_dollar, char *token)
{
	int	i;

	i = 0;
	while (i < *i_dollar)
	{
		res[i] = token[i];
		i++;
	}
	return (i);
}

int	cpy_env_val(char *res, char *row_env, int i_new, int i)
{
	while (row_env[i_new] != '\0')
	{
		res[i] = row_env[i_new];
		i++;
		i_new++;
	}
	return (i);
}
/*
	while (token[i_dollar + tmp + 1] != '\0')
	{
		res[i] = token[i_dollar + tmp + 1];
		i++;
		tmp++;
	}

*/

int	cpy_after_env_var(char *token, char *res, int j, int i)
{
	while (token[j] != '\0')
	{
		res[i] = token[j];
		i++;
		j++;
	}
	return (i);
}

char	*replace_substring_1(char *token, char *row_env, int i_dollar)
{
	int		i;
	int		i_new;
	int		tmp;
	char	*res;

	i = 0;
	i_new = ft_strchr_m(row_env, '=') + 1;
	tmp = i_new - 1;
	res = malloc((ft_strlen(row_env + i_new)
				+ i_dollar + 1 + 100) * sizeof(char));
	if (res == NULL)
		return (NULL);
	i = cpy_until_dollar(res, &i_dollar, token);
	i = cpy_env_val(res, row_env, i_new, i);
	i = cpy_after_env_var(token, res, (i_dollar + tmp + 1), i);
	res[i] = '\0';
	free(token);
	return (res);
}
