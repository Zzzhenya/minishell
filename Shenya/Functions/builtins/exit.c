#include "../minishell.h"

int ft_isanumber(char *str)
{
	int i = 0;
	int sign = 0;

	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
	{
		sign ++;
		i ++;
	}
	while (str[i] != '\0' && ft_isdigit(str[i]))
		i ++;
	if (str[i] != '\0' && !ft_isdigit(str[i]))
		return (0);
	else
		return (i - sign);
}

void	print_exit_error(char *string, char *message)
{
	ft_putstr_fd("bash: exit: ", 2);
	if (string)
		ft_putstr_fd(string, 2);
	ft_putstr_fd(message, 2);
}

static void handle_exit_codes(char **argv, int digcount)
{
	if (digcount && digcount <= 19 && !argv[2])
	{
		if (ft_atoll(argv[1]) >= 0 && ft_atoll(argv[1]) <= 255)
			g_exit_status = ft_atoll(argv[1]);
		else if (ft_atoll(argv[1]) < 0)
			g_exit_status = 256 + ft_atoll(argv[1]);
		else
			g_exit_status = ft_atoll(argv[1]) - 256;
		// free stuff
		exit(g_exit_status);
	}
	else if (digcount && argv[2])
	{
		print_exit_error(NULL,"too many arguments\n");
		g_exit_status = 1;
		return;
	}
}

/* Need to free stuff before exit */

void	exec_exit(char **argv, t_envp *my_data)
{
	(void) my_data;
	int digcount;

	digcount = 0;
	ft_putstr_fd("exit\n", 2);
	if (!argv[1])
	{
		// free stuff
		exit(g_exit_status);
	}
	digcount = ft_isanumber(argv[1]);
	if (digcount)
		handle_exit_codes(argv, digcount);
	else
	{
		print_exit_error(argv[1], ": numeric argument required\n");
		g_exit_status = 255;
		// free stuff
		exit(g_exit_status);
	}
}