#include "../inc/minishell.h"

static int	ft_check_n_echo(char *argv);
static void	ft_echo_no_new_line(char **cmd_splited, int fd);
static void	ft_echo_with_new_line(char **cmd_splited, int fd);

int	echo_builtin(char **cmd_splited, int fd)
{
	if (!cmd_splited)
		return (EXIT_FAILURE);
	if (cmd_splited[1] == NULL)
	{
		ft_putendl_fd("", fd);
		return (EXIT_SUCCESS);
	}
	if (ft_check_n_echo(cmd_splited[1]) == TRUE)
		ft_echo_no_new_line(cmd_splited, fd);
	else
		ft_echo_with_new_line(cmd_splited, fd);
	return (EXIT_SUCCESS);
}

static void	ft_echo_with_new_line(char **cmd_splited, int fd)
{
	int	i;

	i = 1;
	while (cmd_splited[i])
	{
		ft_putstr_fd(cmd_splited[i], fd);
		if (cmd_splited[i + 1] != NULL)
			ft_putstr_fd(" ", fd);
		else
			ft_putendl_fd("", fd);
		i++;
	}
	return ;
}

static void	ft_echo_no_new_line(char **cmd_splited, int fd)
{
	int	i;

	i = 2;
	while (cmd_splited[i])
	{
		ft_putstr_fd(cmd_splited[i], fd);
		if (cmd_splited[i + 1] != NULL)
			ft_putstr_fd(" ", fd);
		i++;
	}
	return ;
}

static int	ft_check_n_echo(char *argv)
{
	int	i;
	int	len;

	if (!argv)
		return (FALSE);
	if (argv[0] != '-')
		return (FALSE);
	len = ft_strlen(argv);
	i = 1;
	while (argv[i] == 'n')
		i++;
	if (i == len)
		return (TRUE);
	return (FALSE);
}
