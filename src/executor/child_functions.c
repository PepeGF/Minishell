/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 12:52:05 by josgarci          #+#    #+#             */
/*   Updated: 2023/04/24 20:47:09 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "builtins.h"

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
	ft_free_matrix(vars.env_dup);
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
	redirect_fd(child->cmd, &fd_in, &fd_out);
	if (child->cmd->cmd_splited == NULL)
		exit(EXIT_SUCCESS);
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

int	pipe_child(t_exec *child, t_command *cmd)
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
		perror("minishell");
		return (FALSE);
	}
}

void	execution_with_child(t_list *aux, t_vars *vars)
{
	t_exec	child;

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
	return ;
}

void	run_child(t_exec *child)
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
