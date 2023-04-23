/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:31:18 by drontome          #+#    #+#             */
/*   Updated: 2023/04/23 19:44:17 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

t_exec	init_child(t_vars *vars)
{
	t_exec	child;

	child.cmd = NULL;
	child.env_dup = vars->env_dup;
	child.paths = get_paths(vars->env_dup);
	child.n_proc = 0;
	child.tot_pr = ft_lstsize(vars->nodes);
	child.last_cmd = 0;
	return (child);
}

t_proc	check_pos(size_t pos, size_t tot)
{
	if (pos == 0 && tot == 1)
		return (UNQ);
	else if (pos == 0)
		return (FIRST);
	else if (pos + 1 == tot)
		return (LAST);
	else
		return (MID);
}

int	ch_pipe_pos(t_exec *child, t_proc pos)
{
	child->pipe_in[RD] = child->pipe_out[RD];
	child->pipe_in[WR] = child->pipe_out[WR];
	if (pos == LAST)
		return (TRUE);
	else if (pos == MID && pipe(child->pipe_out) == 0)
		return (TRUE);
	else
		return (FALSE);
}

void	close_fd(t_exec *child)
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
