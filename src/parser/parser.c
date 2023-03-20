/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:32:07 by drontome          #+#    #+#             */
/*   Updated: 2023/03/16 19:35:14 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


int	redir(char **tokens, int t, t_vars *list)
{
	int len;

	len = ft_strlen(tokens[t]);
	if (len > 2 || !is_redir(tokens[t], tokens[t][0]))
		return (FALSE);
	else if (len == 1 && tokens[t][0] == '<')
		get_infile(list, tokens, t);
	else if (len == 1 && tokens[t][0] == '>')
		get_outfile(list, tokens, t);
	else if (len == 2 && ft_strncmp(tokens[t], ">>", len)
		get_append(list, tokens, t);
	else if (len == 2 && ft_strncmp(tokens[t], "<<", len)
		get_heredoc(list, tokens, t);
	else
		return (FALSE);
}

static void	init_vars(t_vars *vars, char **env_dup, char **tokens)
{
	t_command *node;

	ft_calloc(sizeof(node), 1);
	if (!node)
	{
		ft_free_matrix(tokens);
		error_n_exit(MEM, env_dup);
	}
	vars.env_dup = env_dup;
	vars->nodes = ft_lstnew(node);
	if (vars->nodes == NULL)
	{
		ft_free_matrix(tokens);
		error_n_exit(MEM, env_dup);
	}
	return ;
}


char	*parser(char **tokens, char **env_dup)
{
	t_vars	vars;
	int		t;

	init_vars(&vars, env_dup, tokens);
	t = 0;
	while (tokens && tokens[t])
	{
		redir(tokens, t, &vars);
	}
	return (NULL);
}
