/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:31:18 by drontome          #+#    #+#             */
/*   Updated: 2023/04/18 19:12:11 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "builtins.h"
#include <stdlib.h>

extern int	g_exit;
static int	pipe_child(t_exec *child, t_command *cmd);
static int	fork_child(t_exec *child);
static void	close_fd(t_exec *child);
static void	run_child(t_exec *child);

char	*ft_get_right_path(t_exec *child)
{
	int	i;
	char	*path;

	if (!child)
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

void	redirect_fd(t_exec *child, int *fd_in, int *fd_out)
{
	if (child->cmd->infile != NULL)
		{
			*fd_in = open(child->cmd->infile, O_RDONLY);
			if (*fd_in < 0)
			{
				perror("minishell: ");
				exit(EXIT_FAILURE);
			}
			dup2(*fd_in, STDIN_FILENO);
			close(*fd_in);
		}
		if (child->cmd->outfile != NULL)
		{
			if (child->cmd->flag[APP] == 1)
				*fd_out = open(child->cmd->outfile, O_WRONLY | O_APPEND | O_CREAT);
			else
				*fd_out = open(child->cmd->outfile, O_WRONLY | O_CREAT);
			if (*fd_out < 0)
			{
				perror("minishell: ");
				exit(EXIT_FAILURE);
			}
			dup2(*fd_out, STDOUT_FILENO);
			close(*fd_out);
		}
}

void child_pepe(t_exec *child)
{
	char	*path;
	int		fd_in;
	int		fd_out;

	if (child->cmd->cmd_splited == NULL)
		exit(EXIT_SUCCESS);
	redirect_fd(child, &fd_in, &fd_out);
	if (access(child->cmd->cmd_splited[0], R_OK | X_OK) == 0)
		execve(child->cmd->cmd_splited[0], child->cmd->cmd_splited, child->env_dup);
	else
	{
		path = ft_get_right_path(child);
		if (path)
			execve(path, child->cmd->cmd_splited, child->env_dup);
	}
	exec_error(child, path);
}


void	executor(t_vars *vars)
{
	t_list	*aux;
	t_exec	child;

	aux = (t_list *)vars->nodes;
	if (((t_command *)aux->content)->cmd_splited == NULL)
		return ;
	if (vars->nodes->next == NULL && ft_check_builtin(((t_command *) \
			(vars->nodes->content))->cmd_splited) != -1)
		ft_execute_builtin(vars); // PEPE: añadir builtins en los hijos
	else
	{
		child = init_child(vars);
		while (child.n_proc < child.tot_pr)
		{
			if(!pipe_child(&child, (t_command *)aux->content) || \
				!fork_child(&child))
				break;
			aux = aux->next;
			child.n_proc++;
		}
		if (g_exit == 0) // DANI: checkear esta condición
		{
			waitpid(child.last_cmd, &g_exit, WUNTRACED);
			while(waitpid(-1, NULL, WUNTRACED) > 0);
		}
		ft_free_matrix(child.paths);
	}
}


static int	pipe_child(t_exec *child, t_command *cmd)
{
	child->cmd = cmd;
	if (check_pos(child->n_proc, child->tot_pr) == UNQ)
		return(TRUE);
	else if (check_pos(child->n_proc, child->tot_pr) == FIRST && \
			pipe(child->pipe_out) == 0)
		return(TRUE);
	else if  (check_pos(child->n_proc, child->tot_pr) == LAST && \
			ch_pipe_pos(child, LAST))
		return(TRUE);
	else if ((check_pos(child->n_proc, child->tot_pr) == MID) && \
			ch_pipe_pos(child, MID))
		return(TRUE);
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
		return(child_pepe(child));
	else if (check_pos(child->n_proc, child->tot_pr) == FIRST && \
	dup2(child->pipe_out[WR], STDOUT_FILENO) >= 0)
		close(child->pipe_out[WR]);
	else if (check_pos(child->n_proc, child->tot_pr) == MID && \
	dup2(child->pipe_in[RD], STDIN_FILENO) >= 0 && \
	dup2(child->pipe_out[WR], STDOUT_FILENO) >= 0)
	{
		close(child->pipe_in[RD]);
		close(child->pipe_out[WR]);
	}
	else if (check_pos(child->n_proc, child->tot_pr) == LAST && \
	dup2(child->pipe_in[RD], STDIN_FILENO) >= 0)
		close(child->pipe_in[RD]);
	else
		exit (EXIT_FAILURE);
	return(child_pepe(child));
}




/*
static void	close_and_wait(int *p_end, int child1, int child2)
{
	int	status1;
	int	status2;

	close(p_end[0]);
	close(p_end[1]);
	waitpid(child1, &status1, 0);
	waitpid(child2, &status2, 0);
	if (WIFEXITED(status1))
		status1 = WEXITSTATUS(status1);
	if (WIFEXITED(status2))
		status2 = WEXITSTATUS(status2);
	if (status1 == NO_PATH)
		ft_printf("%sCommand 1 not found or cannot be executed.%s\n", RED, CEND);
	if (status2 == NO_PATH)
		ft_printf("%sCommand 2 not found or cannot be executed.%s\n", RED, CEND);
	exit(status2);
	return ;
}
*/
