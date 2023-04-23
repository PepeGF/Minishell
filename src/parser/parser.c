/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:32:07 by drontome          #+#    #+#             */
/*   Updated: 2023/04/23 13:11:25 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"

extern int	g_exit;

static int	is_empty(char *str);
static void	mem_error_free(t_vars *vars, char **tokens);

int	parser(t_vars *vars, char **tokens)
{
	int		t;
	char	*arg;

	t = 0;
	init_nodes(vars, tokens);
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
				mem_error_free(vars, tokens);
			t++;
		}
	}
	ft_free_matrix(tokens);
	return (g_exit);
}

static void	mem_error_free(t_vars *vars, char **tokens)
{
	free_nodes(vars);
	error_n_exit(MEM, tokens);
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
