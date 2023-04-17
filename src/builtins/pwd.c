#include "../inc/minishell.h"
#include "builtins.h"

int	pwd_builtin(void)
{
	char	*directory;

	directory = getcwd(NULL, 0);
	if (directory)
	{
		ft_putendl_fd(directory, STDOUT_FILENO);
		free(directory);
		return (SUCCESS);
	}
	free(directory);
	g_exit = 1;
	return (FAILURE);
}
