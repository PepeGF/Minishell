/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:32:07 by drontome          #+#    #+#             */
/*   Updated: 2023/04/06 19:12:45 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
extern int	g_exit;

static void	ft_set_shlvl(char ***env_dup);

void	init_vars(t_vars *vars, char **envp)
{
	signal(SIGQUIT, SIG_IGN);
	*vars = (t_vars){};
	if (envp == NULL)
		return;
	vars->env_dup = ft_dup_matrix(envp);
	if (!vars->env_dup)
		error_n_exit(MEM, NULL);
	ft_set_shlvl(&vars->env_dup);
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

void	update_vars(t_vars *vars)
{
	char **cmds;

	cmds = ((t_command *)ft_lstlast(vars->nodes)->content)->cmd_splited;
	if (g_exit > 255)
		g_exit = g_exit % 255;
	if (g_exit == 0 && cmds)
	{
		if (vars->last_arg != NULL)
			free(vars->last_arg);
		if (vars->nodes->next == NULL)
			vars->last_arg = ft_strdup(cmds[ft_len_matrix(cmds) - 1]);
		else
			vars->last_arg = ft_strdup("");
	}
	if (vars->nodes)
		ft_lstclear(&vars->nodes, free_cmd);
	vars->nodes = NULL;
//	printf("%s\n", vars->last_cmd);
}

static void	ft_set_shlvl(char ***env_dup)
{
	char	*shlvl;
	char	*aux;
	int		level;
	char	**env_aux;

	aux = ft_get_value_env(*env_dup, "SHLVL");
	if (aux != NULL)
	{
		level = ft_atoi(aux) + 1;
		shlvl = ft_itoa(level);
		free(aux);
		aux = ft_strjoin("SHLVL=", shlvl);
		free(shlvl);
		ft_replace_line_in_matrix(*env_dup, aux);
		free(aux);
	}
	else
	{
		env_aux = ft_add_line_to_matrix(env_dup, "SHLVL=1");
		*env_dup = env_aux;
	}
}
