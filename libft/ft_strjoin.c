/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 17:10:38 by mandriic          #+#    #+#             */
/*   Updated: 2021/10/01 17:10:42 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		count;
	int		count2;

	if (!s1 || !s2)
		return (0);
	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (NULL == p)
		return (0);
	count = 0;
	while (s1[count] != '\0')
	{
		p[count] = s1[count];
		count++;
	}
	count2 = 0;
	while (s2[count2] != '\0')
	{
		p[count] = s2[count2];
		count++;
		count2++;
	}
	p[count] = '\0';
	return (p);
}
