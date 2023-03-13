/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:42:43 by drontome          #+#    #+#             */
/*   Updated: 2023/03/13 20:18:24 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_var(char *str, int i);


int is_inquotes(char *str, char *var, char br)
{
	int count;

	count = 0;
	while (str && *str && str < var)
	{
		if (*str == br)
		{
			if (count == 0 && str < var)
				count = 1;
			else if (count == 1 && str < var)
				count = 0;
		}
		str++;
	}
	return (count);
}

int	check_var(char *str, int i)
{
	if (str[i] == '$' && is_inquotes(str, str + i, '\'') == 0)
		return (TRUE);
	else if (str[i] ==  '~' && \
		(str[i + 1] == ' ' || str[i + 1] == '/' || str[i + 1] == '\0'))
	{
		if ((i > 0 && str[i - 1] != ' ') || is_inquotes(str, str + i, '\'') \
			|| is_inquotes(str, str + i, '\"'))
			return (FALSE);
		else
			return (TRUE);
	}
	else
		return (FALSE);
}
