/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:31:18 by drontome          #+#    #+#             */
/*   Updated: 2023/04/21 19:17:26 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "executor.h"
#include "builtins.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static int	pipe_child(t_exec *child, t_command *cmd);
static int	fork_child(t_exec *child);
static void	close_fd(t_exec *child);
static void	run_child(t_exec *child);

char	*ft_get_right_path(t_exec *child)
{
	int		i;
	char	*path;

	if (!child || child->paths == NULL)
		return (NULL);
	i = 0;
	while (child->paths[i])
	{
		path = ft_strjoin(child->paths[i], child->cmd->cmd_splited[0]);
		if (path == NULL)
			i++;
		else if (access(path, X_OK) != 0)
		{
			free(path);
			i++;
		}
		else
			return (path);
	}
	return (NULL);
}

void	redirect_fd(t_command *cmd, int *fd_in, int *fd_out)
{
	if (cmd->infile != NULL)
	{
		*fd_in = open(cmd->infile, O_RDONLY);
		if (*fd_in < 0)
			exit(p_error(FD, 0, cmd->infile));
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
	}
	if (cmd->outfile != NULL)
	{
		if (cmd->flag[APP] == 1)
			*fd_out = open(cmd->outfile, O_WRONLY | O_APPEND | O_CREAT);
		else
			*fd_out = open(cmd->outfile, O_WRONLY | O_CREAT);
		if (*fd_out < 0)
			exit(p_error(FD, 0, cmd->outfile));
		dup2(*fd_out, STDOUT_FILENO);
		close(*fd_out);
	}
}

void	ft_execve_child_to_vars(t_exec *child)
{
	t_vars	vars;
	int		status;

	vars.nodes = ft_lstnew((void *)child->cmd);
	if (vars.nodes == NULL)
	{
		free_cmd((void *)child->cmd);
		ft_free_matrix(child->paths);
		rl_clear_history();
		error_n_exit(MEM, child->env_dup);
	}
	vars.env_dup = child->env_dup;
	status = ft_execute_builtin(&vars);
	ft_lstclear(&vars.nodes, free_cmd);
	ft_free_matrix(child->env_dup);
	ft_free_matrix(child->paths);
	rl_clear_history();
	exit(status);
}

void	ft_child(t_exec *child)
{
	char	*path;
	int		fd_in;
	int		fd_out;

	path = NULL;
	if (child->cmd->cmd_splited == NULL)
		exit(EXIT_SUCCESS);
	redirect_fd(child->cmd, &fd_in, &fd_out);
	if (ft_check_builtin(child->cmd->cmd_splited) >= 0)
		ft_execve_child_to_vars(child);
	else if (access(child->cmd->cmd_splited[0], R_OK | X_OK) == 0)
		execve(child->cmd->cmd_splited[0], child->cmd->cmd_splited,
			child->env_dup);
	else
	{
		path = ft_get_right_path(child);
		if (path)
			execve(path, child->cmd->cmd_splited, child->env_dup);
	}
	exec_error(child, path);
}

void	ft_set_underscore(t_list *node, char ***env_dup, char **cmd_splited)
{
	int		i;
	char	*aux;

	if (node != NULL || env_dup == NULL || *env_dup == NULL
		|| cmd_splited == NULL || cmd_splited[0] == NULL)
		return ;
	i = 0;
	while (cmd_splited[i])
		i++;
	aux = ft_strjoin("_=", cmd_splited[i - 1]);
	if (ft_check_already_in_env(*env_dup, "_") == TRUE)
	{
		if (ft_replace_line_in_matrix(*env_dup, aux) == FAILURE)
			free (aux);
		free(aux);
		return ;
	}
	else
		*env_dup = ft_add_line_to_matrix(env_dup, aux);
	free(aux);
}

void	executor(t_vars *vars)
{
	t_list	*aux;
	t_exec	child;

	aux = (t_list *)vars->nodes;
	if (((t_command *)aux->content)->cmd_splited == NULL)
		return ;
	if (vars->nodes->next == NULL)
		ft_set_underscore(aux->next, &vars->env_dup, \
			(((t_command *)aux->content)->cmd_splited));
	if (vars->nodes->next == NULL && ft_check_builtin(((t_command *) \
			(vars->nodes->content))->cmd_splited) >= 0)
		g_exit = ft_execute_builtin(vars);
	else
	{
		child = init_child(vars);
		while (child.n_proc < child.tot_pr)
		{
			if (!pipe_child(&child, (t_command *)aux->content) || \
				!fork_child(&child))
				break ;
			aux = aux->next;
			child.n_proc++;
		}
		wait_childs(child.last_cmd);
		ft_free_matrix(child.paths);
	}
}

static int	pipe_child(t_exec *child, t_command *cmd)
{
	child->cmd = cmd;
	if (check_pos(child->n_proc, child->tot_pr) == UNQ)
		return (TRUE);
	else if (check_pos(child->n_proc, child->tot_pr) == FIRST && \
			pipe(child->pipe_out) == 0)
		return (TRUE);
	else if (check_pos(child->n_proc, child->tot_pr) == LAST && \
			ch_pipe_pos(child, LAST))
		return (TRUE);
	else if ((check_pos(child->n_proc, child->tot_pr) == MID) && \
			ch_pipe_pos(child, MID))
		return (TRUE);
	else
	{
		g_exit = 1;
		perror("minishell: ");
		return (FALSE);
	}
}

static int	fork_child(t_exec *child)
{
	pid_t	id;

	id = fork();
	if (id < 0)
	{
		g_exit = 1;
		perror("minishell: ");
		return (FALSE);
	}
	else if (id == 0)
		run_child(child);
	else
	{
		if (child->n_proc + 1 == child->tot_pr)
			child->last_cmd = id;
		close_fd(child);
	}
	return (TRUE);
}

static void	close_fd(t_exec *child)
{
	if (check_pos(child->n_proc, child->tot_pr) == UNQ)
		return ;
	else if (check_pos(child->n_proc, child->tot_pr) == FIRST)
		close(child->pipe_out[WR]);
	else if (check_pos(child->n_proc, child->tot_pr) == MID)
	{
		close(child->pipe_in[RD]);
		close(child->pipe_out[WR]);
	}
	else if (check_pos(child->n_proc, child->tot_pr) == LAST)
		close(child->pipe_in[RD]);
	return ;
}

static void	run_child(t_exec *child)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (check_pos(child->n_proc, child->tot_pr) == UNQ)
		return (ft_child(child));
	else if (check_pos(child->n_proc, child->tot_pr) == FIRST && \
	dup2(child->pipe_out[WR], STDOUT_FILENO) >= 0)
	{
		close(child->pipe_out[WR]);
		close(child->pipe_out[RD]);
	}
	else if (check_pos(child->n_proc, child->tot_pr) == MID && \
	dup2(child->pipe_in[RD], STDIN_FILENO) >= 0 && \
	dup2(child->pipe_out[WR], STDOUT_FILENO) >= 0)
	{
		close(child->pipe_in[RD]);
		close(child->pipe_out[WR]);
		close(child->pipe_out[RD]);
	}
	else if (check_pos(child->n_proc, child->tot_pr) == LAST && \
	dup2(child->pipe_in[RD], STDIN_FILENO) >= 0)
		close(child->pipe_in[RD]);
	else
		exit (EXIT_FAILURE);
	return (ft_child(child));
}
