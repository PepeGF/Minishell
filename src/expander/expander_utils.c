/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:42:43 by drontome          #+#    #+#             */
/*   Updated: 2023/03/15 20:57:40 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_var(char *str, int i)
{
	if (str[i] == '$' && !is_inquotes(str, str + i, "\'"))
		return (TRUE);
	else if (str[i] == '~' && \
		(str[i + 1] == ' ' || str[i + 1] == '/' || str[i + 1] == '\0'))
	{
		if ((i > 0 && str[i - 1] != ' ') || is_inquotes(str, str + i, "\'\""))
			return (FALSE);
		else
			return (TRUE);
	}
	else
		return (FALSE);
}

char	*change_str(char *str, int i, char *value, char *var)
{
	char	*new;

	printf("LA ANTIGUA STR ES %s\n\n", str);
	new = ft_substr(str, 0, i);
	if (value != NULL)
		new = ft_strjoin_free(new, value);
	new = ft_strjoin_free(new, ft_substr(str, i + ft_strlen(var), \
		ft_strlen(str + i + ft_strlen(var))));
	if (new)
		printf("LA NUEVA STR ES %s\n\n", new);
	free(str);
	return (new);
}
