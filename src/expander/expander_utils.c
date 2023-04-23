/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:42:43 by drontome          #+#    #+#             */
/*   Updated: 2023/04/23 12:27:05 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit;

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

	new = ft_substr(str, 0, i);
	if (value != NULL)
		new = ft_strjoin_free(new, value);
	else if (ft_strncmp(var, "$?", ft_strlen(var)) == 0)
		new = ft_strjoin_free(new, ft_itoa(g_exit));
	new = ft_strjoin_free(new, ft_substr(str, i + ft_strlen(var), \
		ft_strlen(str + i + ft_strlen(var))));
	free(str);
	return (new);
}

int	next_hedoc(char **tokens, int t)
{
	int	len;

	if (t < 1)
		return (FALSE);
	len = ft_strlen(tokens[t - 1]);
	if (len == 2 && ft_strncmp("<<", tokens[t - 1], len) == 0)
		return (TRUE);
	else
		return (FALSE);
}
