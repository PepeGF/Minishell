/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:32:07 by drontome          #+#    #+#             */
/*   Updated: 2023/03/16 19:35:14 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int get_infile(t_vars *vars, char **tokens, int t)
{
	t_command	*node;
	char *file;

	
	node = (t_command *)vars->nodes->content;
	if (node->infile != 0)
		close(node->infile);

}



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

