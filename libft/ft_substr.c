/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 16:33:58 by mandriic          #+#    #+#             */
/*   Updated: 2021/10/01 16:34:03 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
static char	*ft_asign(char const *s, unsigned int start, size_t len, int size)
{
	char	*p;
	size_t	count;

	p = (char *)malloc(sizeof(char) * size + 1);
	if (NULL == p)
		return (0);
	count = 0;
	while (s[start] != '\0' && len != 0)
	{
		p[count] = s[start];
		start++;
		count++;
		len--;
	}
	p[count] = '\0';
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		size;

	if (!s)
		return (NULL);
	if (ft_strlen(s) > start)
	{
		if (ft_strlen(s) >= start + len)
			size = len;
		else
			size = ft_strlen(s) - start;
	}
	else
		return (ft_strdup(""));
	return (ft_asign(s, start, len, size));
}