/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:14:31 by drontome          #+#    #+#             */
/*   Updated: 2023/03/01 20:22:30 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cross_string(char *s, size_t *i)
{
	char	c;
	size_t		len;

	len = 0;
	if (*s == '\'' || *s == '\"')
	{
		c = *s;
		len++;
	}
	else
		c = ' ';
	if (*s == c)
		s++;
	while (*s && (*s != c && (c != ' ' || (*s != '\'' && *s != '\"'))))
	{
		if (c == ' ' && (*s == '\'' || *s == '\"'))
			break;
		s++;
		len++;
	}
	if (*s == c && *s != ' ')
	{
		s++;
		len++;
	}
	if (i)
		*i = len;
	return (s);
}

static size_t count_tokens(char *s)
{
	size_t i;
	// char *aux;

	// aux = s;
	i = 0;
	while (s && *s)
	{
		while (s && *s && *s == ' ')
			s++;
		if (*s)// && (s == aux || (*s != ' ' && *(s - 1) == ' ')))
			i++;
		s = cross_string(s, NULL);
	}
	return (i);
}

static size_t ft_count_string(char *s)
{
	size_t i;

	i = 0;
	if (*s == '\'' || *s == '\"')
		s = cross_string(s, &i);
	else
	{
		while (*s && ft_strchr("\'\" ", *s) == 0)
		{
			i++;
			s++;
		}
	}
	return (i);
}

static char **ft_free_null(char **pp, size_t i)
{
	while (i--)
	free(pp[i]);
	free(pp);
	return (NULL);
}

char **smart_split(char *s)
{
	char **pp;
	size_t len;
	size_t i;

	if (!s)
		return (NULL);
	len = count_tokens(s);
	if (len == 0)
			return (NULL);
	pp = ft_calloc(len + 1, sizeof(s));
	if (!pp)
		return (NULL);
	i = 0;
	while (*s && i < len)
	{
		while (*s && *s == ' ')
			s++;
		pp[i] = ft_substr(s, 0, ft_count_string(s));
		if (!pp[i])
			return (ft_free_null(pp, i));
		if (*s)
			s = cross_string(s, NULL);
		i++;
	}
	return (pp);
}
