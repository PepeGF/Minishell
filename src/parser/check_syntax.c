/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:44:32 by drontome          #+#    #+#             */
/*   Updated: 2023/03/20 12:45:14 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*check_syntax(char **tokens)
{
	t = 0;
	while (tokens && tokens[t])
	{
		redir(tokens, t, &vars);
	}
	return (NULL);
}
