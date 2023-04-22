/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:44:52 by josgarci          #+#    #+#             */
/*   Updated: 2023/04/20 18:33:00 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "builtins.h"

int	ft_check_builtin(char **cmd_splitted)
{
	char	*builtins[8];
	int		i;

	if (!cmd_splitted)
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
		if (ft_strncmp(cmd_splitted[0], builtins[i],
				ft_strlen(builtins[i]) + 1) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_run_builtin(char **cmd_splitted, t_vars *vars, int cmd)
{
	if (cmd == PWD)
		return (pwd_builtin());
	else if (cmd == CD)
		return (cd_builtin(&(vars->env_dup), cmd_splitted));
	else if (cmd == EXPORT)
		return (export_builtin(&(vars->env_dup), vars->nodes));
	else if (cmd == UNSET)
		return (unset_builtin(&(vars->env_dup), vars->nodes));
	else if (cmd == ENV)
		return (env_builtin(vars->env_dup));
	else if (cmd == ECHOO)
		return (echo_builtin(cmd_splitted, 1));
	else if (cmd == EXIT)
		return (exit_builtin(cmd_splitted));
	else
		return (-1);
}

int	ft_execute_builtin(t_vars *vars)
{
	int		cmd;
	char	**cmd_splitted;
	int		std_fd[2];
	int		status;

	cmd_splitted = ((t_command *)(vars->nodes->content))->cmd_splited;
	cmd = ft_check_builtin(((t_command *)(vars->nodes->content))->cmd_splited);
	if (cmd >= 0)
	{
		if (ft_redirect_builtins(((t_command *)(vars->nodes->content)), \
			&std_fd[1], &std_fd[0]))
			return (FAILURE);
		status = ft_run_builtin(cmd_splitted, vars, cmd);
		if (ft_recorver_std_fd(((t_command *)(vars->nodes->content)), std_fd))
			return (FAILURE);
	}
	else
		status = SUCCESS;
	return (status);
}
