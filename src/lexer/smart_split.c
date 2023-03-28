/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:14:31 by drontome          #+#    #+#             */
/*   Updated: 2023/03/15 19:02:38 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_tokens(char *s);
static char		*cross_string(char *s, size_t *i);
static char		*get_end_str(char *s, char c, size_t *len, int count);
static size_t	count_string(char *s);

char	**smart_split(char *s)
{
	char	**pp;
	size_t	len;
	size_t	i;

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
		while (*s && (*s == ' ' || *s == '\t'))
			s++;
		pp[i] = ft_substr(s, 0, count_string(s));
		if (!pp[i])
			return (ft_free_matrix(pp));
		if (*s)
			s = cross_string(s, NULL);
		i++;
	}
	return (pp);
}

static size_t	count_tokens(char *s)
{
	size_t	i;

	i = 0;
	while (s && *s)
	{
		while (s && *s && (*s == ' ' || *s == '\t'))
			s++;
		if (*s)
			i++;
		s = cross_string(s, NULL);
	}
	return (i);
}

static char	*cross_string(char *s, size_t *i)
{
	char	c;
	size_t	len;
	int		count;

	c = 0;
	len = 0;
	count = 0;
	if (*s == '\'' || *s == '\"')
	{
		c = *s;
		count = 1;
		len++;
	}
	if (*s && (*s == c || *s == ' ' || *s == '\t'))
		s++;
	s = get_end_str(s, c, &len, count);
	if (i)
		*i = len;
	return (s);
}

static char	*get_end_str(char *s, char c, size_t *len, int count)
{
	while (*s && ((*s != ' ' && *s != '\t') || ((*s == ' ' && count == 1)
				|| (*s == '\t' && count == 1))))
	{
		if (c != 0 && (*s == c))
		{
			count = !count;
			c = 0;
		}
		else if (c == 0 && (*s == '\'' || *s == '\"'))
		{
			c = *s;
			count = !count;
		}
		s++;
		*len = *len + 1;
	}
	return (s);
}

static size_t	count_string(char *s)
{
	size_t	i;

	i = 0;
	cross_string(s, &i);
	return (i);
}
