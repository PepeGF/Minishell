/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:32:07 by drontome          #+#    #+#             */
/*   Updated: 2023/04/05 19:32:01 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_vars(t_vars *vars, char **envp)
{
	signal(SIGQUIT, SIG_IGN);
	if (envp == NULL)
	{
		*vars = (t_vars){};
		return;
	}
	vars->nodes = NULL;
	vars->env_dup = ft_dup_matrix(envp);
	if (!vars->env_dup)
		error_n_exit(MEM, NULL);
}

void	init_nodes(t_vars *vars, char **tokens)
{
	vars->nodes = ft_lstnew(init_cmd());
	if (vars->nodes == NULL || vars->nodes->content == NULL)
	{
		ft_free_matrix(tokens);
		ft_lstclear(&vars->nodes, free);
		error_n_exit(MEM, vars->env_dup);
	}
}

t_command	*init_cmd(void)
{
	t_command	*cmd;

	cmd = ft_calloc(sizeof(t_command), sizeof(char));
	if (!cmd)
		return (NULL);
	return (cmd);
}

void	free_nodes(t_vars *vars)
{
	if (vars->nodes)
		ft_lstclear(&vars->nodes, free_cmd);
	vars->nodes = NULL;
}

void	free_cmd(void *content)
{
	t_command	*cmd;

	cmd = (t_command *)content;
	if (cmd->cmd_splited)
		ft_free_matrix(cmd->cmd_splited);
	if (cmd->infile)
	{
		if (cmd->flag[HER])
			unlink(cmd->infile);
		free(cmd->infile);
	}
	if (cmd->outfile)
		free(cmd->outfile);
	free(cmd);
}

