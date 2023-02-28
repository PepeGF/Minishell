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

char *parser(char *line)
{
	char **tokens;
	int i;

	i = 0;
	if (!line)// || ft_strncmp("exit", line, ft_strlen("exit")))
	{
		printf("exit\n");
		return(NULL);
	}
	else if (*line != '\0')
	{
		add_history(line);
		tokens = smart_split(line);
		while (tokens && tokens[i])
		{
			printf("TOKENIZADOR ACTIVO: %s\n", tokens[i]);
			i++;
		}
	}
	ft_free_matrix(tokens);
	return (NULL);
}
