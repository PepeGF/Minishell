/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:42:43 by drontome          #+#    #+#             */
/*   Updated: 2023/03/16 19:39:09 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_var(char *str, int i);
char		*change_str(char *str, int i, char *value, char *var);
int			next_hedoc(char **tokens, int t);
static void	expand_var(char **tokens, int t, int i, char **env_dup);
static void	expand_home(char **tokens, int t, int i, char **env_dup);
static char	*grep_var(char *str);
static char	*grep_value(char *var, char **env);

char	**expander(char **tokens, char **env_dup)
{
	int	i;
	int	t;

	if (!tokens)
		return (NULL);
	t = 0;
	while (tokens[t])
	{
		i = 0;
		while (tokens[t] && tokens[t][i] != '\0')
		{
			if (tokens[t][i] == '$' && check_var(tokens[t], i) \
				&& !next_hedoc(tokens, t))
				expand_var(tokens, t, i, env_dup);
			else if (tokens[t][i] == '~' && check_var(tokens[t], i) \
				&& !next_hedoc(tokens, t))
				expand_home(tokens, t, i, env_dup);
			if (tokens[t][i] != '\0')
				i++;
		}
		t++;
	}
	return (tokens);
}

static void	expand_var(char **tokens, int t, int i, char **env_dup)
{
	char	*var;
	char	*value;

	var = grep_var(&tokens[t][i]);
	value = grep_value(var, env_dup);
	tokens[t] = change_str(tokens[t], i, value, var);
	if (var)
	{
		printf("LA VARIABLE ES %s\n\n", var);
		free (var);
	}
}

static void	expand_home(char **tokens, int t, int i, char **env_dup)
{
	char	*home;

	home = grep_value("$HOME", env_dup);
	if (!home)
		return ;
	tokens[t] = change_str(tokens[t], i, home, "~");
}

static char	*grep_value(char *var, char **env)
{
	char	*aux;
	char	*str;

	if (!var)
		return (NULL);
	aux = ft_strjoin(var, "=");
	str = NULL;
	if (aux)
	{
		aux++;
		while (env && *env)
		{
			if (ft_strncmp(aux, *env, ft_strlen(aux)) == 0)
			{
				str = (ft_substr(*env, ft_strlen(aux), \
					ft_strlen(*env) - (ft_strlen(aux))));
				break ;
			}
			env++;
		}
		if (aux)
			free(--aux);
	}
	return (str);
}

static char	*grep_var(char *str)
{
	int		i;
	char	*var;

	i = 1;
	var = NULL;
	while (str && ft_isalnum(str[i]))
		i++;
	if (i < 2)
		return (NULL);
	var = ft_substr(str, 0, i);
	return (var);
}

/* CAMBIANDO ESTO POR is_alnum: str[i] && str[i] != ' ' && str[i] != '\"' && \
		str[i] != '\\' && str[i] != '/')
*/
