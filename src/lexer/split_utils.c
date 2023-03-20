/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:53:57 by drontome          #+#    #+#             */
/*   Updated: 2023/03/15 19:03:07 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(char *str, char *red)
{
	int	i;

	i = 0;
	if (red == NULL)
	{
		while (str && str[i])
		{
			if (ft_strchr("<>|", str[i]) != 0 && \
				!is_inquotes(str, str + i, "\'\""))
				return (TRUE);
			else
				i++;
		}
	}
	else
	{
		if (!ft_strchr("<>|", *red))
			return (FALSE);
		else if (!is_inquotes(str, red, "\'\""))
			return (TRUE);
	}
	return (FALSE);
}

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

int	is_inquotes(char *str, char *var, char *qu)
{
	int		count;
	char	*aux;

	count = 0;
	aux = str;
	while (qu && *qu)
	{
		while (str && *str && str < var)
		{
			if (*qu == '\'' && *str == '\'' && is_inquotes(aux, str, "\""))
				str++;
			else if (*str == *qu)
			{
				if (count == 0 && str < var)
					count = 1;
				else if (count == 1 && str < var)
					count = 0;
				str++;
			}
			else
				str++;
		}
		if (count == 1)
			return (count);
		qu++;
		str = aux;
	}
	return (count);
}
