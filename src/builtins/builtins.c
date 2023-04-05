#include "../inc/minishell.h"

int	exit_builtin(void)
{
	exit(EXIT_SUCCESS);
}

int	pwd_builtin(void)
{
	char	*directory;

	directory = getcwd(NULL, 0);
	if (directory)
	{
		ft_putendl_fd(directory, STDOUT_FILENO);
		free(directory);
		return (0);
	}
	free(directory);
	//si hay error directory == NULL, en ese caso
	//establecer valor de error (no consigo que el original falle)
	//perror("mensaje de error")
	return (EXIT_FAILURE);
}

int	env_builtin(char **env_dup)
{
	int	i;

	if (env_dup == NULL)
	{
		//print error
		ft_putendl_fd("Minishell: env: No such file or directory",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (env_dup[i])
	{
		ft_putendl_fd(env_dup[i], STDERR_FILENO);
		i++;
	}
	return (0);
}

int	ft_check_builtin(char **cmd_splitted)
{
	char	*builtins[8];
	int		i;
	if(!cmd_splitted)//esto es para evitar segfault en pruebas
		return (-2);
	builtins[0] = "pwd";
	builtins[1] = "cd";
	builtins[2] = "export";
	builtins[3] = "unset";
	builtins[4] = "env";
	builtins[5] = "echo";
	builtins[6] = "exit";
	builtins[7] = NULL;
	i = 0;
	while (builtins[i])
	{
		if (ft_strncmp(cmd_splitted[0], builtins[i], ft_strlen(builtins[i] + 1)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_execute_builtin(t_vars *vars)
{
	int		cmd;
	char	**cmd_splitted;

	cmd_splitted = ((t_command *)(vars->nodes->content))->cmd_splited;
	cmd = ft_check_builtin(((t_command *)(vars->nodes->content))->cmd_splited);
	if (cmd == PWD)
		return (pwd_builtin());
	if (cmd == CD)
		return (cd_builtin(&(vars->env_dup), cmd_splitted));
	if (cmd == EXPORT)
		return (export_builtin(&(vars->env_dup), vars->nodes));
	if (cmd == UNSET)
		return (unset_builtin(&(vars->env_dup), vars->nodes));
	if (cmd == ENV)
		return (env_builtin(vars->env_dup));
	if (cmd == ECHO)
		return (echo_builtin(cmd_splitted, 1));
	if (cmd == EXIT)
		return (exit_builtin());
	return (-1);
}