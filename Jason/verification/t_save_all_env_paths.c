#include "../../include/minishell.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (str1[i] && str2[i] && str1[i] == str2[i] && i < (n - 1))
		i++;
	if (str1[i] == str2[i])
		return (0);
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

int	countrow(char const *s, char c)
{
	char	prvc;
	int		index;
	int		row;

	row = 0;
	index = 0;
	prvc = 0;
	if (s[index] != c && s[index] != 0)
		row ++;
	while (s[index])
	{
		if (prvc == c && s[index] != c)
			row ++;
		prvc = s[index];
		index ++;
	}
	if (c == 0)
		row = row - 1;
	return (row);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (res == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tmp;
	size_t	index;

	index = 0;
	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (tmp == NULL)
		return (NULL);
	while (index < len && s[start + index] != '\0')
	{
		tmp[index] = s[start + index];
		index++;
	}
	tmp[index] = '\0';
	return (tmp);
}

int	tool4free(char **str, int i4str)
{
	if (str[i4str] == NULL)
	{
		while (i4str >= 0)
			free(str[i4str--]);
		free(str);
		return (-1);
	}
	return (1);
}

// [M]
char	**linebyline(char **str, char const *s, char c)
{
	int	i;
	int	i4str;
	int	start;

	i = 0;
	i4str = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			str[i4str] = ft_substr(s, start, i - start);
			if (str[i4str] == NULL)
			{
				tool4free(str, i4str);	// 할당 실패 시 메모리 해제 후 종료
				return (NULL);
			}
			i4str++;
		}
		else
			i++;
	}
	str[i4str] = NULL;
	return (str);
}

// [M]
char	**ft_split(char const *s, char c)
{
	char	**str;
	int		row;

	row = countrow(s, c);
	str = (char **)malloc((row + 1) * sizeof(char *));
	if (!str || !s)
		return (NULL);
	str = linebyline(str, s, c);
	if (str == NULL) // linebyline 호출 실패 시 메모리 해제
	{
		free (str);
		return (NULL);
	}
	return (str);
}

char	**save_all_env_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			// int j = 0;
			// while (envp[i][j])
			// {
			// 	printf("envp[%d][%d]: %c\n", i, j, envp[i][j]);
			// 	j++;
			// }
			return (ft_split(&envp[i][ft_strlen("PATH=")], ':'));
		}
		i++;
	}
	perror("save_all_env_paths: ");
	exit(EXIT_FAILURE);
}

void	free_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}

int	main(int argc, char **argv, char **envs)
{
	t_cmd	*tree;
	t_envp	env;
	char	**paths;

	env.envp = envs;
	(void)argv;
	(void)argc;
	paths = save_all_env_paths(envs);
	if (argc == 2)
	{
		int i = 0;
		while (paths[i] != NULL)
		{
			printf("paths[%d]:%s\n", i, paths[i]);
			i++;
		}
	}
	free_2d(paths);
}

/*
char	*get_allocated_cwd(void)
{
	int		i;
	char	*cwd;

	cwd = malloc(1024 * sizeof(char));
	if (cwd == NULL)
		return (NULL);
	getcwd(cwd, 1024);
	i = ft_strlen(cwd);
	cwd[i] = ' ';
	cwd[i + 1] = '\0';
	return (cwd);
}

void	non_interactive_mode(t_cmd **tree,
								char *input, char **envp, t_envp *env)
{
	char	**user_inputs;
	int		i;

	user_inputs = ft_split(input, ';');
	i = 0;
	while (user_inputs[i])
	{
		*tree = parse_user_input(user_inputs[i], env);
		search_tree(*tree, envp, env);
		i++;
		free_tree(*tree);
	}
	free_2d(user_inputs);
}
*/