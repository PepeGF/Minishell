/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:32:07 by drontome          #+#    #+#             */
/*   Updated: 2023/03/20 12:20:29 by drontome         ###   ########.fr       */
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

static int	check_quotes(char *line)
{
	int	qu;

	qu = 0;
	while (line && *line)
	{
		if (ft_strchr("\'\"", *line))
		{
			if (qu == 0)
				qu = *line;
			else if (qu == *line)
				qu = 0;
		}
		line++;
	}
	return (qu);
}

char	*lexer(char *line, char **env)
{
	char	**tokens;

	tokens = NULL;
	if (check_quotes(line))
		p_error(SYN, "while looking for matching quote");
	else if (*line != '\0')
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
