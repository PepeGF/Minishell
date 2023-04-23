/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:32:07 by drontome          #+#    #+#             */
/*   Updated: 2023/04/23 13:02:49 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static int	check_quotes(char *line);
/*
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
*/

char	**lexer(char *line, char **env_dup)
{
	char	**tokens;
	char	qu;

	tokens = NULL;
	qu = check_quotes(line);
	if (qu != 0)
		p_error(QU, qu, "\'");
	else if (ft_strncmp(line, "\n", ft_strlen(line) == 0))
		return (NULL);
	else if (*line != '\0')
	{
		add_history(line);
		tokens = smart_split(line);
		tokens = redir_split(tokens);
		tokens = expander(tokens, env_dup);
	}
	free(line);
	if (tokens && check_syntax(tokens))
		return (tokens);
	else
	{
		ft_free_matrix(tokens);
		return (NULL);
	}
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
