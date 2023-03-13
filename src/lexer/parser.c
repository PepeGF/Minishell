/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:42:43 by drontome          #+#    #+#             */
/*   Updated: 2023/03/13 20:43:29 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t count_newtokens(char **tokens)
{
	int       i;
	int       t;
	size_t    len;

	t = 0;
	len = 0;
	while(tokens[t])
	{
		i = 0;
		len++;
		while (tokens[t][i] != 0)
		{
			if (ft_strchr("<>|", tokens[t][i]) != 0 && \
				!is_inquotes(tokens[t], &tokens[t][i], '\'') && \
				!is_inquotes(tokens[t], &tokens[t][i], '\"'))
			{
				len++;
				if (i > 0 && tokens[t][i + 1] != 0)
					len++;
			}
			i++;
		}
		t++;
	}
	return (len);
}

static int is_redir(char *str)
{
	int i;

	i = 0;
	while(str && str[i])
	{
		if (ft_strchr("<>|", str[i]) != 0 && \
			!is_inquotes(str, &str[i], '\'') && \
			!is_inquotes(str, &str[i], '\"'))
			return (1);
		else
			i++;
	}
	return (0);
}
 //REPASAR EL SPLIT AL PRINCIPIO Y AL FINAL, HAY QUE METER EN EL BUCLE
static char **fill_split(char **new_tokens, char *str)
{
	int i;

	i = 0;
	while(str[i] != 0 && ft_strchr("<>|", str[i]) == 0)
		i++;
	if (i > 0)
	{
		*new_tokens = ft_substr(str, 0, i);
		new_tokens++;
		*new_tokens = ft_substr(str, i, 1);
	}
	else
		*new_tokens = ft_substr(str, 0, 1);
	if (str[i] != 0 && str[i + 1] != 0)
	{
		new_tokens++;
		*new_tokens = ft_substr(str, i + 1, ft_strlen(str + i + 1));
	}
	return (new_tokens);
}

char **redir_split(char **tokens)
{
	char **new_tokens;
    char **aux;
    char **aux_new;
	size_t  len;


    aux = tokens;
	if (!tokens)
		return (NULL);
	len = count_newtokens(tokens);
	if (len <= (size_t)ft_len_matrix(tokens))
		return (tokens);
	new_tokens = ft_calloc(len + 1, sizeof(tokens));
	if(!new_tokens)
		error_n_exit(MEM, tokens);
	aux_new = new_tokens;
	while(tokens && *tokens && new_tokens)
	{
		if(is_redir(*tokens))
			new_tokens = fill_split(new_tokens, *tokens);
		else
			*new_tokens = ft_strdup(*tokens);
		tokens++;
		new_tokens++;
	}
	ft_free_matrix(aux);
	return (aux_new);
}

char *parser(char *line, char **env_dup)
{
	char **tokens;
	int i;

	tokens = NULL;
	i = 0;
	if (!line)
	{
		printf("exit\n");
		return(NULL);
	}
	else if (*line != '\0')
	{
		add_history(line);
		tokens = smart_split(line);
		tokens = redir_split(tokens);
		env_dup = (char **)env_dup;
//		expander(tokens, env_dup);
		while (tokens && tokens[i])
		{
			printf("TOKENIZADOR ACTIVO: #%s#\n", tokens[i]);
			i++;
		}
	}
	// if (tokens)
		// ft_free_matrix(tokens);
	return (NULL);
}
