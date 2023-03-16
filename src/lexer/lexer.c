/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:32:07 by drontome          #+#    #+#             */
/*   Updated: 2023/03/16 19:35:14 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_tokens(char **tokens)
{
	int	count;

	count = 1;
	printf("%sLEXER ACTIVO, SE MOSTRARÁN LOS TOKENS EXPANDIDOS:%s\n", \
		RED, CEND);
	while (tokens && *tokens)
	{
		printf("\t%d. #%s#\n", count, *tokens);
		tokens++;
		count++;
	}
	printf("%sLEXER FINALIZADO%s\n", RED, CEND);
}

char	*lexer(char *line, char **env)
{
	char	**tokens;

	tokens = NULL;
	if (*line != '\0')
	{
		add_history(line);
		tokens = smart_split(line);
		tokens = redir_split(tokens);
		tokens = expander(tokens, env);
	}
	if (tokens)
	{
		print_tokens(tokens);
		ft_free_matrix(tokens);
	}
	return (NULL);
}
