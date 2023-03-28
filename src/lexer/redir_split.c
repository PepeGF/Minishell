/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:31:38 by drontome          #+#    #+#             */
/*   Updated: 2023/03/15 20:42:26 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static char	**check_tokens(char **tokens);
static char	**fill_token(char **new_tokens, char *str);
static char	**add_redir(char **new_tokens, char *str, int *i, int *len);
static char	**add_reminder(char **new_tokens, char *str, int start, int len);

char	**redir_split(char **tokens)
{
	char	**new_tokens;
	char	**aux;
	char	**aux_new;

	new_tokens = check_tokens(tokens);
	if (new_tokens == NULL || new_tokens == tokens)
		return (new_tokens);
	aux = tokens;
	aux_new = new_tokens;
	while (tokens && *tokens && new_tokens)
	{
		if (is_redir(*tokens, NULL))
			new_tokens = fill_token(new_tokens, *tokens);
		else
		{
			*new_tokens = ft_strdup(*tokens);
			new_tokens++;
		}
		tokens++;
	}
	ft_free_matrix(aux);
	return (aux_new);
}

static char	**check_tokens(char **tokens)
{
	size_t	len;
	char	**new_tokens;

	if (tokens == NULL)
		return (NULL);
	len = count_newtokens(tokens);
	if (len <= (size_t)ft_len_matrix(tokens))
		return (tokens);
	new_tokens = ft_calloc(len + 1, sizeof(tokens));
	if (!new_tokens)
	{
		free(tokens);
		return (NULL);
	}
	return (new_tokens);
}

static char	**fill_token(char **new_tokens, char *str)
{
	int	i;
	int	len;
	int	start;

	i = 0;
	len = 0;
	start = 0;
	while (str[i] != 0)
	{
		if (!is_redir(str, str + i))
		{
			i++;
			len++;
			continue ;
		}
		if (len)
		{
			*new_tokens = ft_substr(str, start, len);
			new_tokens++;
		}
		new_tokens = add_redir(new_tokens, str, &i, &len);
		start = i;
	}
	new_tokens = add_reminder(new_tokens, str, start, len);
	return (new_tokens);
}

static char	**add_redir(char **new_tokens, char *str, int *i, int *len)
{
	if (is_app_or_her(str, str + *i))
	{
		*new_tokens = ft_substr(str, *i, 2);
		(*i)++;
	}
	else
		*new_tokens = ft_substr(str, *i, 1);
	new_tokens++;
	(*i)++;
	*len = 0;
	return (new_tokens);
}

static char	**add_reminder(char **new_tokens, char *str, int start, int len)
{
	if (len)
	{
		*new_tokens = ft_substr(str, start, len);
		new_tokens++;
	}
	return (new_tokens);
}
