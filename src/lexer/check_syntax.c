/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:44:32 by drontome          #+#    #+#             */
/*   Updated: 2023/03/20 12:45:14 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit;

static int	valid_redir(char **tokens, int t, int redir)
{
	if (redir == '|' && t == 0)
		p_error(SYN, redir, "\'");
	else if (tokens[t + 1] == NULL)
		p_error(SYN, 0, "newline\'");
	else if (redir != '|' && is_redir(tokens[t + 1], tokens[t + 1]))
		p_error(SYN, tokens[t + 1][0], "\'");
	else
		return (TRUE);
	g_exit = 2;
	return (FALSE);
}

int	check_syntax(char **tokens)
{
	int	t;

	t = 0;
	while (tokens && tokens[t])
	{
		if (is_redir(tokens[t], tokens[t]) && \
			!valid_redir(tokens, t, tokens[t][0]))
			return (FALSE);
		t++;
	}
	return (TRUE);
}
