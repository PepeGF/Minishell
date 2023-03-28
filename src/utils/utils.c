/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:57:44 by drontome          #+#    #+#             */
/*   Updated: 2023/03/28 11:57:46 by drontome         ###   ########.fr       */
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
			if (*str == *qu && \
				!(*qu == '\'' && *str == '\'' && is_inquotes(aux, str, "\"")))
			{
				if (count == 0 && str < var)
					count = 1;
				else if (count == 1 && str < var)
					count = 0;
			}
			str++;
		}
		if (count == 1)
			return (count);
		qu++;
		str = aux;
	}
	return (count);
}
