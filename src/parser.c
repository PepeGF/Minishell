/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:42:43 by drontome          #+#    #+#             */
/*   Updated: 2023/02/26 20:46:32 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *parser(char *line)
{
	if (!line || ft_strncmp("exit", line, ft_strlen("exit")))
	{
		printf("exit\n");
		return(NULL);
	}
	else if (*line != '\0')
		add_history(line);

	return (NULL);
}
