/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:31:18 by drontome          #+#    #+#             */
/*   Updated: 2023/04/24 20:45:17 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "builtins.h"

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

void	ft_set_underscore(t_list *node, char ***env_dup, char **cmd_splited)
{
	int		i;
	char	*aux;

	if (env_dup == NULL || *env_dup == NULL
		|| cmd_splited == NULL || cmd_splited[0] == NULL)
		return ;
	i = 0;
	while (cmd_splited[i])
		i++;
	if (node != NULL)
		aux = ft_strdup("_=\n");
	else
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

	aux = (t_list *)vars->nodes;
	if ((((t_command *)(aux->content))->cmd_splited) == NULL &&
		(((t_command *)(aux->content))->infile) == NULL &&
		(((t_command *)(aux->content))->outfile) == NULL)
		return ;
	ft_set_underscore(aux->next, &vars->env_dup, \
			(((t_command *)aux->content)->cmd_splited));
	if (aux->next == NULL && ft_check_builtin(((t_command *) \
			(aux->content))->cmd_splited) >= 0)
		g_exit = ft_execute_builtin(vars);
	else
		execution_with_child(aux, vars);
}

int	fork_child(t_exec *child)
{
	pid_t	id;

	id = fork();
	if (id < 0)
	{
		g_exit = 1;
		perror("minishell");
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
