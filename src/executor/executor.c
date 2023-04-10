/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:31:18 by drontome          #+#    #+#             */
/*   Updated: 2023/04/07 21:31:24 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include <stdlib.h>

extern int	g_exit;
static int	pipe_child(t_exec *child, t_command *cmd);
static int	fork_child(t_exec *child);
static void	close_fd(t_exec *child);
static int	execve_child(t_exec *child);

int child_pepe(t_exec *child)
{
	char *str;
	int	n;

	child =(t_exec *)child;
	
	n = 0;
	str = ft_itoa(n + 1);
	ft_putstr(str);
	free(str);
	if (child->n_proc + 1 == child->tot_pr)
		ft_putstr("\n");
	exit(EXIT_SUCCESS);
	return (TRUE);
}


void	executor(t_vars *vars)
{
	t_list	*aux;
	t_exec	child;

	aux = (t_list *)vars->nodes;
	child = init_child(vars);
	while (child.n_proc < child.tot_pr)
	{
		if(!pipe_child(&child, (t_command *)aux->content) || \
			!fork_child(&child))
			break;
		aux = aux->next;
		child.n_proc++;
	}
	waitpid(-1, NULL, WUNTRACED);
	ft_free_matrix(child.paths);
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
		g_exit = errno;
		perror("pipe");
		return (FALSE);
	}
}

static int	fork_child(t_exec *child)
{
	pid_t	id;

	id = fork();
	if (id < 0)
	{
		g_exit = errno;
		perror("fork");
		return (FALSE);
	}
	else if (id == 0)
		execve_child(child);
	else
	 	close_fd(child);
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

static int	execve_child(t_exec *child)
{
	if (check_pos(child->n_proc, child->tot_pr) == UNQ)
		return(child_pepe(child));
	else if (check_pos(child->n_proc, child->tot_pr) == FIRST)
	{
		dup2(child->pipe_out[WR], STDOUT_FILENO); // mejorar caso de fallo
		close(child->pipe_out[WR]);
		return(child_pepe(child));
	}
	else if (check_pos(child->n_proc, child->tot_pr) == MID)
	{
		dup2(child->pipe_in[RD], STDIN_FILENO);
		close(child->pipe_in[RD]);
		dup2(child->pipe_out[WR], STDOUT_FILENO);
		close(child->pipe_out[WR]);
		return(child_pepe(child));
	}
	else if (check_pos(child->n_proc, child->tot_pr) == LAST)
	{
		dup2(child->pipe_in[RD], STDIN_FILENO);
		close(child->pipe_in[RD]);
		return(child_pepe(child));
	}
	return (FALSE);
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
