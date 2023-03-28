/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:53:57 by drontome          #+#    #+#             */
/*   Updated: 2023/03/20 12:25:21 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_app_or_her(char *str, char *red)
{
	if (!ft_strchr("<>", *red))
		return (FALSE);
	else if (!is_inquotes(str, red, "\'\"") && *red == *(red + 1))
		return (TRUE);
	else
		return (FALSE);
}

size_t	count_newtokens(char **tokens)
{
	int		i;
	size_t	len;

	len = 0;
	while (tokens && *tokens)
	{
		i = 0;
		len++;
		while ((*tokens)[i] != 0 && ft_strlen(*tokens) > 1)
		{
			if (is_app_or_her(*tokens, (*tokens) + i))
			{
				if (i > 0)
					len++;
				i++;
			}
			else if (is_redir(*tokens, (*tokens) + i) && i > 0)
				len++;
			else if (i > 0 && is_redir(*tokens, (*tokens) + i - 1))
				len++;
			i++;
		}
		tokens++;
	}
	return (len);
}
