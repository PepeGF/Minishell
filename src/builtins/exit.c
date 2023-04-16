#include "../inc/minishell.h"
#include "builtins.h"

extern int	g_exit;

static int	ft_isnumber(char *str);
static int	ft_exit_error_no_number(char *str);
static int	ft_exit_with_arg(char *str);

int	exit_builtin(char **cmd_splitted)
{
	if (ft_len_matrix(cmd_splitted) > 2)
	{
		ft_putendl_fd("Minishell: exit: too many arguments", 2);
		g_exit = 255;
		exit(EXIT_FAILURE);
	}
	else if (ft_len_matrix(cmd_splitted) == 2)
	{
		if (ft_isnumber(cmd_splitted[1]) == FALSE)
			exit (ft_exit_error_no_number(cmd_splitted[1]));
		else
			exit (ft_exit_with_arg(cmd_splitted[1]));
	}
	else
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}

int	ft_isnumber(char *str)
{
	int	i;

	if (!str)
		return (FALSE);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_exit_error_no_number(char *str)
{
	ft_putstr_fd("Minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	g_exit = 255;
	exit(EXIT_FAILURE);
}

int	ft_exit_with_arg(char *str)
{
	int	num;

	num = ft_atoi(str) % 256;
	if (num < 0)
		num = 256 + num;
	g_exit = num;
	ft_putendl_fd("exit", STDOUT_FILENO);
	
	return (WEXITSTATUS(num));
}
