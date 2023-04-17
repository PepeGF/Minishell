#include "../inc/minishell.h"
#include "builtins.h"

int	env_builtin(char **env_dup)
{
	int	i;

	if (env_dup == NULL)
	{
		ft_putendl_fd("minishell: env: No such file or directory",
			STDERR_FILENO);
		g_exit = 127;
		return (FAILURE);
	}
	i = 0;
	while (env_dup[i])
	{
		ft_putendl_fd(env_dup[i], STDOUT_FILENO);
		i++;
	}
	return (SUCCESS);
}
