/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:12:26 by mandriic          #+#    #+#             */
/*   Updated: 2021/10/01 12:12:30 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*p;
	int		count;

	if (s == NULL)
		return (NULL);
	p = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (NULL == p)
		return (0);
	count = 0;
	while (s[count] != '\0')
	{
		p[count] = s[count];
		count++;
	}
	p[count] = '\0';
	return (p);
}
