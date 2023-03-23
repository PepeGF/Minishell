#include "../inc/minishell.h"

int	echo_builtin(char **cmd_splited, int fd)
{
	int	i;

	if (!cmd_splited)
		return (EXIT_FAILURE);
	if (cmd_splited[1] == NULL)
		return (EXIT_SUCCESS);
	if (ft_check_n_echo(cmd_splited[1]) == TRUE)
	{
		i = 2;
		while(cmd_splited[i])
		{
			ft_putstr_fd(cmd_splited[i], fd);
			if (cmd_splited[i + 1] != NULL)
				ft_putstr_fd(" ", fd);
			i++;
		}
	}
	else
	{
		i = 1;
		while (cmd_splited[i])
		{
			ft_putstr_fd(cmd_splited, fd);
			if (cmd_splited[i + 1] != NULL)
				ft_putstr_fd(" ", fd);
			else
				ft_putendl_fd("", fd);
			i++;
		}
	}
	return (EXIT_SUCCESS);
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

