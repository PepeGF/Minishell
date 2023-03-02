/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:42:43 by drontome          #+#    #+#             */
/*   Updated: 2023/03/02 19:25:44 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_inbrackets(char *str, char *var, char br);
int		check_var(char *str, int i);


int is_inbrackets(char *str, char *var, char br)
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
	if (str[i] == '$' && is_inbrackets(str, str + i, '\'') == 0)
		return (TRUE);
	else if (str[i] ==  '~' && \
		(str[i + 1] == ' ' || str[i + 1] == '\\' || str[i + 1] == '\0'))
		return (TRUE);
	else
		return (FALSE);
}
