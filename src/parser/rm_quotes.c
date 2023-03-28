/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:32:07 by drontome          #+#    #+#             */
/*   Updated: 2023/03/16 19:35:14 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	len_no_qu(char *str);

char	*rm_quotes(char *str)
{
	char	*new_str;
	char	qu;
	int		i;

	if (ft_strlen(str) == len_no_qu(str))
		return (ft_strdup(str));
	qu = 0;
	i = 0;
	new_str = ft_calloc(sizeof(char), len_no_qu(str) + 1);
	if (!new_str)
		return (NULL);
	while (str && *str)
	{
		if (ft_strchr("\'\"", *str) && qu == 0)
			qu = *str;
		else if (ft_strchr("\'\"", *str) && qu == *str)
			qu = 0;
		else
		{
			new_str[i] = *str;
			i++;
		}
		str++;
	}
	return (new_str);
}

static size_t	len_no_qu(char *str)
{
	int	len;
	int	qu;

	len = 0;
	qu = 0;
	while (str && *str)
	{
		if (ft_strchr("\'\"", *str) && qu == 0)
			qu = *str;
		else if (ft_strchr("\'\"", *str) && qu == *str)
			qu = 0;
		else
			len++;
		str++;
	}
	return (len);
}
