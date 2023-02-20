#include "../inc/minishell.h"

void    ft_echo(char **str)
{
	int 	i;
	int 	j;
	bool	newline;

	i = 1;
	newline = true;
	if (str[i] && ft_strncmp("-n", str[i], 2) == 0)
	{
		j = 2;
		while (str[i][j] == 'n')
			j++;
	}
	if (str[i][j] == '\0')
	{
		newline = false;
		i++;
	}
	while (str[i])
	{
		ft_putstr_fd(str[i], STDOUT_FILENO);
		if (str[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline == true)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return;
}