/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:32:07 by drontome          #+#    #+#             */
/*   Updated: 2023/03/20 20:24:45 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static int	is_empty(char *str);
extern int	g_exit;

t_vars	*parser(char **tokens, char **env_dup)
{
	int		t;
	t_vars	*vars;
	char	*arg;

	t = 0;
	vars = init_vars(env_dup, tokens);
	while (tokens && tokens[t] && g_exit != 130)
	{
		if (is_empty(tokens[t]))
			t++;
		else if (get_redir(tokens, t, vars))
			t = t + 2;
		else if (get_pipe(tokens, t, vars))
			t++;
		else
		{
			arg = rm_quotes(tokens[t]);
			if (!arg || !get_arg(arg, vars))
			{
				free_vars(vars);
				error_n_exit(MEM, tokens);
			}
			t++;
		}
	}
	ft_free_matrix(tokens);
	return (vars);
}

static int	is_empty(char *str)
{
	if (!str || *str == '\0')
		return (TRUE);
	else
		return (FALSE);
}

//	t_command *cmd;
/*	if (vars.nodes)
	{
		cmd = (t_command *)(vars.nodes->content);
		printf("PROBANDO LAS LISTAS:\n\tinfile: %d\n\toutfile: %d\n\tcmd: %p\n",
				cmd->infile, cmd->outfile, NULL);
	} */
