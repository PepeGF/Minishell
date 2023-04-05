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

int	init_vars(t_vars *vars, char **tokens)
{
/* 	t_vars	*vars;

	vars = malloc(sizeof(t_vars));
	if (!vars)
	{
		ft_free_matrix(tokens);
		error_n_exit(MEM, env_dup);
	}
	vars->env_dup = env_dup;
*/
	vars->nodes = ft_lstnew(init_cmd());
	if (vars->nodes == NULL || vars->nodes->content == NULL)
	{
		ft_free_matrix(tokens);
		ft_lstclear(&vars->nodes, free);
		error_n_exit(MEM, vars->env_dup);
	}
	return (EXIT_SUCCESS);
}

t_command	*init_cmd(void)
{
	t_command	*cmd;

	cmd = ft_calloc(sizeof(t_command), sizeof(char));
	if (!cmd)
		return (NULL);
	return (cmd);
}

void	free_vars(t_vars *vars)
{
	//if (vars->env_dup)
	//	ft_free_matrix(vars->env_dup);
	if (vars->nodes)
		ft_lstclear(&vars->nodes, free_cmd);
	// free(vars);
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
