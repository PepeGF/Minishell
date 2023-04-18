/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:44:52 by josgarci          #+#    #+#             */
/*   Updated: 2023/04/17 22:44:58 by josgarci         ###   ########.fr       */
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

int	ft_redirect_builtins(t_command *cmd, int *stdout_fd)
{
	int fd_out;

	if (cmd->outfile != NULL)
	{
		*stdout_fd = dup(STDOUT_FILENO);
		if (cmd->flag[APP] == 1)
			fd_out = open(cmd->outfile, O_WRONLY | O_APPEND | O_CREAT);
		else
			fd_out = open(cmd->outfile, O_WRONLY | O_CREAT);
		if (fd_out < 0)
		{
			perror("minishell");
			return(FAILURE);
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		// printf("ufffffff al archivo\n"); esto es para probar
		// dup2(*stdout_fd, STDOUT_FILENO); esto es para deshacer la redirección y volver a esrcibir en stdout 1
		// close(*stdout_fd); esto tb es para lo mismo
	}
	return (SUCCESS);
}

int	ft_execute_builtin(t_vars *vars)
{
	int		cmd;
	char	**cmd_splitted;
	int		std_fd[2];
//int status;
	cmd_splitted = ((t_command *)(vars->nodes->content))->cmd_splited;
	cmd = ft_check_builtin(((t_command *)(vars->nodes->content))->cmd_splited);
	if (cmd >= 0)
	{
		if (ft_redirect_builtins(((t_command *)(vars->nodes->content)), &std_fd[1]))
			return (-2);//impplementarlo en llamada
	}
	if (cmd == PWD)
		return (pwd_builtin());
		// status = (pwd_builtin());
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
		return (exit_builtin(cmd_splitted));

	//desredreccionar
	return (-1);
}
