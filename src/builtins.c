#include "../inc/minishell.h"

void	ft_echo_builtin(t_command cmd, t_vars *vars)
{
    (void)cmd;
}
void	ft_cd_builtin(t_command cmd, t_vars *vars)
{
    // (void)cmd;
	ft_chdir(vars);
}

void	ft_pwd_builtin(t_command cmd, t_vars *vars)
{
    (void)cmd;
    char	*directory;

	directory = getcwd(NULL, MAXPATHLEN);
	// if (directory == NULL) ->gestión error de getcwd
	ft_putstr_fd(directory, 1);
    ft_putstr_fd("\n", 1);
    // código salida de ejecución
	free(directory);
	return ;
}

void	ft_env_builtin(t_command cmd, t_vars *vars)
{
    int i;
    (void)cmd;
    //gestion errores entrada
    i = 0;
	printf("SOY BUILTIN\n");
    while (vars->env_var[i])
    {
        printf("%s\n", vars->env_var[i]);
        i++;
    }
    //estado de salida
}

void	ft_exit_builtin(t_command cmd, t_vars *vars)
{
    (void)cmd;
}

bool	ft_is_builtin(t_command cmd)//pasar puntero y proteger??
{
	if (ft_strncmp("echo", cmd.comando_a_pelo, ft_strlen("echo")) == 0
		|| ft_strncmp("cd", cmd.comando_a_pelo, ft_strlen("cd")) == 0
		|| ft_strncmp("pwd", cmd.comando_a_pelo, ft_strlen("pwd")) == 0
		|| ft_strncmp("export", cmd.comando_a_pelo, ft_strlen("export")) == 0
		|| ft_strncmp("unset", cmd.comando_a_pelo, ft_strlen("unset")) == 0
		|| ft_strncmp("env", cmd.comando_a_pelo, ft_strlen("env")) == 0
		|| ft_strncmp("exit", cmd.comando_a_pelo, ft_strlen("exit")) == 0)
		return (true);
	return (false);
	/* echo, cd, pwd, export, unset, env, exit */
}

void	ft_execute_buitlin(t_command cmd, t_vars *vars)
{

	if (ft_strncmp("echo", cmd.comando_a_pelo, ft_strlen("echo")) == 0)
		ft_echo_builtin(cmd, vars);
	if (ft_strncmp("cd", cmd.comando_a_pelo, ft_strlen("cd")) == 0)
		ft_cd_builtin(cmd, vars);
	if (ft_strncmp("pwd", cmd.comando_a_pelo, ft_strlen("pwd")) == 0)
		ft_pwd_builtin(cmd, vars);
	if (ft_strncmp("export", cmd.comando_a_pelo, ft_strlen("export")) == 0)
		ft_export_builtin(cmd, vars);
	if (ft_strncmp("unset", cmd.comando_a_pelo, ft_strlen("unset")) == 0)
		ft_unset_builtin(cmd, vars);
	if (ft_strncmp("env", cmd.comando_a_pelo, ft_strlen("env")) == 0)
		ft_env_builtin(cmd, vars);
	if (ft_strncmp("exit", cmd.comando_a_pelo, ft_strlen("exit")) == 0)
		ft_exit_builtin(cmd, vars);
	/* echo, cd, pwd, export, unset, env, exit */
}