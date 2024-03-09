#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_envp
{
	char	**env;
	char	*cd_hist;
	int		count;
}	t_envp;

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len ++;
	return (len);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i] != '\0')
			i ++;
		return (i);
	}
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i ++;
	}
	if (i < size)
		dest [i] = '\0';
	while (src[i] != '\0')
		i ++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;

	ptr = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, ft_strlen(s) + 1);
	return (ptr);
}
int get_len(char **envp)
{
	int i = 0;

	while (envp[i] != NULL)
	{
		i ++;
	}
	return (i);
}

void free_prev(char **env, int len)
{
	int i = 0;

	while (i < len)
	{
		free(env[i]);
		env[i] = NULL;
		i ++;
	}
	free(env);
	env = NULL;
}

int store_envp(t_envp *vars, char **envp)
{
	int len;
	int i = 0;
	
	len = get_len(envp);
	vars->env = malloc(sizeof(char *) * len + 1);
	if (!vars->env)
		return (-1);
	vars->env[len] = NULL;
	while (i < len)
	{
		vars->env[i] = ft_strdup(envp[i]);
		if (!vars->env[i])
		{
			free_prev(vars->env, i);
			return (-1);
		}
		i ++;
	}
	vars->count = len;
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_envp	vars;
	int i = 0;

	//env.envp = envp;
	vars.cd_hist = NULL;
	vars.count = 0;
	store_envp(&vars, envp);
	printf("%d\n", argc);
	(void)argv;
	while (i  < vars.count)
	{
		printf("%s\n", vars.env[i]);
		i ++;
	}
	return (0);
}