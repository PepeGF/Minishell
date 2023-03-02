/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:42:43 by drontome          #+#    #+#             */
/*   Updated: 2023/03/02 20:49:51 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *grep_value(char *var, char **env);
int		is_inbrackets(char *str, char *var, char br);
int		check_var(char *str, int i);
static void	expand_var(char **tokens, char *str, int i, char **env_dup);
//static void	expand_home(char **tokens, char *str, int i, char **env_dup);
static char	*grep_var(char *str);

void	expand_var(char **tokens, char *str, int i, char **env_dup)
{
	char *var;
	char *value;

	var = grep_var(str + i);
	if (var == NULL)
		return ;
	value = grep_value(var + 1, env_dup);
	tokens = (char **)tokens;
	printf("LA VARIABLE ES %s\n\n", var);
	printf("EL VALOR ES %s\n\n", value);
	free (var);
}

//void	expand_home(char **tokens, char *str, int i, char **env_dup)


char *grep_value(char *var, char **env)
{
	while(env && *env)
	{
		if (ft_strncmp(var, *env, ft_strlen(var)) == 0)
		{
			return(ft_substr(*env, ft_strlen(var) + 1, ft_strlen(*env) - (ft_strlen(var) + 1)));
		}
		env++;
	}
	return (NULL);
}

char *grep_var(char *str)
{
	int i;
	char *var;

	i = 1;
	var = NULL;
	while(str && str[i] && str[i] != ' ' && str[i] != '\"' && str[i] != '\\' && str[i] != '/')
		i++;
	if (i < 2)
		return(NULL);
	var = ft_substr(str, 0, i);
	return(var);
}

char **expander(char **tokens, char **env_dup)
{
	int i;
	char **aux;

	if (!tokens || !env_dup)
		return(NULL);
	aux = tokens;
	while(aux && *aux)
	{
		i = 0;
		while (*aux && (*aux)[i] != '\0')
		{
			if ((*aux)[i] == '$' && check_var(*aux, i))
				expand_var(tokens, *aux, i, env_dup);
//			else if ((*aux)[i] == '$' && check_var(*aux, i))
//				expand_home(tokens, *aux, i, env_dup);
			i++;
		}
		aux++;
	}
	return (NULL);
}
