/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:42:43 by drontome          #+#    #+#             */
/*   Updated: 2023/02/28 21:07:10 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_var(char *str, int i, char **env_dup)
{
	if (str[i] == '~' && ft_strchr(str, '\'') < str + i ||\
		ft_strchr(str, '\") < str + i)

	
}

char **expander(char **tokens, char **env_dup)
{
	int i;

	while(tokens && *tokens)
	{
		i = 0;
		while (*tokens[i] != '\0')
		{
			if (ft_strchr("~$", *tokens[i]) != 0)
				check_var(*tokens, i, env_dup);
			i++;
		}
		tokens++;
	}
}
