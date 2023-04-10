/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:31:18 by drontome          #+#    #+#             */
/*   Updated: 2023/04/09 16:45:42 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

static char	**get_paths(char **envp);
static void	add_slash(char **paths);

t_exec	init_child(t_vars *vars)
{
	t_exec child;

	child.cmd = NULL;
	child.env_dup = vars->env_dup;
	child.paths = get_paths(vars->env_dup);
	child.n_proc = 0;
	child.tot_pr = ft_lstsize(vars->nodes); 
	return (child);
}

t_proc check_pos(size_t pos, size_t tot)
{
	if (pos == 0 && tot == 1 )
		return(UNQ);
	else if (pos == 0)
		return(FIRST);
	else if (pos + 1 == tot)
		return(LAST);
	else
		return(MID);
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

static char	**get_paths(char **envp)
{
	char	*path_var;
	char	**paths;

	path_var = NULL;
	while (!path_var && envp && *envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			path_var = *envp;
		envp++;
	}
	if (!path_var)
		return (NULL);
	paths = ft_split(ft_strchr(path_var, '=') + 1, ':');
	add_slash(paths);
	return (paths);
}

static void	add_slash(char **paths)
{
	char	*temp;
	int		i;

	temp = NULL;
	i = 0;
	while (paths[i])
	{
		temp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		if (temp)
			free(temp);
		temp = NULL;
		i++;
	}
	return ;
}
