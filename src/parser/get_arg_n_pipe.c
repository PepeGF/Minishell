/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_n_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:32:07 by drontome          #+#    #+#             */
/*   Updated: 2023/04/03 14:46:44 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static int	free_new_cmd(char **new_cmd, char *arg);

int	get_pipe(char **tokens, int t, t_vars *vars)
{
	t_list	*node;

	if (ft_strncmp(tokens[t], "|", ft_strlen(tokens[t])))
		return (FALSE);
	node = ft_lstnew(init_cmd());
	if (!node || !node->content)
	{
		free_nodes(vars);
		error_n_exit(MEM, tokens);
	}
	ft_lstadd_back(&vars->nodes, node);
	return (TRUE);
}

int	get_arg(char *arg, t_vars *vars)
{
	char	**cmd;
	char	**new_cmd;
	int		i;

	cmd = ((t_command *)ft_lstlast(vars->nodes)->content)->cmd_splited;
	new_cmd = malloc(sizeof(char *) * (ft_len_matrix(cmd) + 2));
	if (!new_cmd)
		return (free_new_cmd(new_cmd, arg));
	i = 0;
	while (cmd && cmd[i])
	{
		new_cmd[i] = ft_strdup(cmd[i]);
		if (!new_cmd[i])
			return (free_new_cmd(new_cmd, arg));
		i++;
	}
	new_cmd[i] = ft_strdup(arg);
	if (!new_cmd[i])
		return (free_new_cmd(new_cmd, arg));
	new_cmd[++i] = NULL;
	free(arg);
	ft_free_matrix(cmd);
	((t_command *)ft_lstlast(vars->nodes)->content)->cmd_splited = new_cmd;
	return (TRUE);
}

static int	free_new_cmd(char **new_cmd, char *arg)
{
	if (new_cmd)
		ft_free_matrix(new_cmd);
	if (arg)
		free(arg);
	return (FALSE);
}
