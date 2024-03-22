#include "fork.h"

int		g_exit_status = 0;

void clean_argv(char **argv, int argc)
{
	int i = 0;

	while (i < argc)
	{
		free (argv[i]);
		argv[i] = NULL;
		i ++;
	}
	free (argv);
	argv = NULL;
}

void free_arr(char **env, int len)
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

void free_string(void	*input)
{
	char *str;

	str = (char *)input;
	free (str);
	str = NULL;
}

void clear_envlist(t_envp *my_data)
{
	ft_lstclear(&my_data->envlist, free_string);
}

void	get_env_var(char *name)
{
	char *ret = NULL;

	ret = getenv(name);
	if (ret == NULL)
	{
		printf(" :getenv error\n");
		return;
	}
	else
		printf("%s\n", ret);
}

int store_envp(t_envp *vars, char **envp)
{
	int 	i;
	char *temp;

	i = 0;
	temp = NULL;
	while (envp[i] != NULL)
	{
		temp = ft_strdup(envp[i]);
		if (!temp)
		{
			//free_list(vars->envlist);
			return (-1);
		}
		ft_lstadd_back(&vars->envlist, ft_lstnew(temp));
		temp = NULL;
		i ++;
	}
	return (0);
}

int extract_envarr(t_envp *my_data)
{
	t_list	*current;
	int i = 0;

	int len = 0;

    current = NULL;
	current = (my_data->envlist);
	len = ft_lstsize(current);
	my_data->envarr = (char **)malloc(sizeof(char *) * (len + 1));
	if (!my_data->envarr)
		return (-1);
	my_data->envarr[len] = NULL;
	while (current != NULL)
	{
		my_data->envarr[i] = ft_strdup((char *)current->content);
		if (!my_data->envarr[i])
		{
			//free_arr(vars->envp, i);
			return (-1);
		}
		current = current->next;
		i ++;
	}
	my_data->count = i;
	return (0);
}

void    clear_envarr(t_envp *my_data)
{
    int i = 0;

    while (my_data->envarr[i] != NULL)
    {
        free(my_data->envarr[i]);
        my_data->envarr[i] = NULL;
        i ++;
    }
    free(my_data->envarr);
    my_data->envarr = NULL;
}


int main (int argc, char **argv, char **envp)
{
	t_envp	my_data;
	char *str = "export PATH=\"HAHA\"";
	char **arr = NULL;
	pid_t pid;

	my_data.envarr = NULL;
	my_data.cd_hist = NULL;
	my_data.envlist = NULL;
	my_data.count = 0;
	(void)argc;
	(void)argv;
	store_envp(&my_data, envp);
	arr = ft_splitbyspace(str);
	printf("\nPATH changed from parent here:\n");
	exec_export(arr, &my_data);
	//exec_unset(arr, &my_data);
	extract_envarr(&my_data);
	printf("\ngetenv from parent:\n\n");
	get_env_var("PATH");
	pid= fork();
	if (pid == -1)
	{
		printf("Fork error\n");
		return (1);
	}
	if (pid == 0)
	{
		if (execve("path", NULL, my_data.envarr) == -1)
		{
			printf("execve error\n");
			return (1);
		}
	}
	else
	{
		wait(NULL);
		printf("\ngetenv from parent: \n\n");
		get_env_var("PATH");
	}
	clean_argv(arr, get_arg_count(arr));
    clear_envarr(&my_data);
    clear_envlist(&my_data);
	return (0);
}