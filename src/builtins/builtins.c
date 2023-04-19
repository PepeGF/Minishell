/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JoseGF <JoseGF@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:44:52 by josgarci          #+#    #+#             */
/*   Updated: 2023/04/19 19:02:08 by JoseGF           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "builtins.h"

static int	ft_perror(void);

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

static int	ft_redirect_out(t_command *cmd, int *stdout_fd)
{
	int fd_out;

	*stdout_fd = dup(STDOUT_FILENO);
	if (cmd->flag[APP] == 1)
		fd_out = open(cmd->outfile, O_WRONLY | O_APPEND | O_CREAT);
	else
		fd_out = open(cmd->outfile, O_WRONLY | O_CREAT);
	if (fd_out < 0)
		return (ft_perror());
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (ft_perror());
	if (close(fd_out) == 1)
		return (ft_perror());
	return (SUCCESS);
}

int	ft_redirect_builtins(t_command *cmd, int *stdout_fd, int *stdin_fd)
{
	int	fd_in;

	if (cmd->outfile != NULL)
		return (ft_redirect_out(cmd, stdout_fd));
	if (cmd->infile != NULL)
	{
		*stdin_fd = dup(STDIN_FILENO);
		fd_in = open(cmd->infile, O_RDONLY);
	if (fd_in < 0)
		return (ft_perror());
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (ft_perror());
	if (close(fd_in) == 1)
		return (ft_perror());
	}
	return (SUCCESS);
}

int	ft_recorver_std_fd(t_command *cmd, int std_fd[2])
{
	if (cmd->outfile != NULL)
	{
		if (dup2(std_fd[1], STDOUT_FILENO) == -1)
			return (ft_perror());
		if (close(std_fd[1]))
			return (ft_perror());
	}
	if (cmd->infile != NULL)
	{
		if (dup2(std_fd[0], STDIN_FILENO) == -1)
			return (ft_perror());
		if (close(std_fd[0]))
			return (ft_perror());
	}
	return (SUCCESS);
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
		if (ft_redirect_builtins(((t_command *)(vars->nodes->content)), &std_fd[1], &std_fd[0]))
			return (-2);//impplementarlo en llamada
	}
	if (cmd == PWD)
		status = pwd_builtin();
	else if (cmd == CD)
		status = cd_builtin(&(vars->env_dup), cmd_splitted);
	else if (cmd == EXPORT)
		status = export_builtin(&(vars->env_dup), vars->nodes);
	else if (cmd == UNSET)
		status = unset_builtin(&(vars->env_dup), vars->nodes);
	else if (cmd == ENV)
		status = env_builtin(vars->env_dup);
	else if (cmd == ECHO)
		status = echo_builtin(cmd_splitted, 1);
	else if (cmd == EXIT)
		status = exit_builtin(cmd_splitted);
	if (cmd >= 0)
	{
		if (ft_recorver_std_fd(((t_command *)(vars->nodes->content)), std_fd))
			return (-3);
	}
	else
		status = -1;
	//desredreccionar
	return (status);
}

static int	ft_perror(void)
{
	perror("minishell");
	return(FAILURE);
}
