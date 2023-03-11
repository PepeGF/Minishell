/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:42:43 by drontome          #+#    #+#             */
/*   Updated: 2023/03/11 15:50:52 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *grep_value(char *var, char **env);
int		is_inbrackets(char *str, char *var, char br);
int		check_var(char *str, int i);
static void	expand_var(char **tokens, int t, int i, char **env_dup);
//static void	expand_home(char **tokens, char *str, int i, char **env_dup);
static char	*grep_var(char *str);

static char *change_str(char *str, int i, char *value, char *var)

{
    char *new;

    printf("LA ANTIGUA STR ES %s\n\n", str);
    printf("LA LONGITUD ES %d\n\n", i);
    new = ft_substr(str, 0, i);
    new = ft_strjoin_free(new, value);
    new =  ft_strjoin_free(new, ft_substr(str, i + ft_strlen(var), ft_strlen(str + i + ft_strlen(var))));
    if (new)
        printf("LA NUEVA STR ES %s\n\n", new);
    free(new);
    return (NULL);
}

static void	expand_var(char **tokens, int t, int i, char **env_dup)
{
	char *var;
	char *value;

	var = grep_var(&tokens[t][i]);
	value = grep_value(var, env_dup);
	if (value == NULL)
		return ;
    else
        tokens[t] = change_str(tokens[t], i, value, var);
	printf("LA VARIABLE ES %s\n\n", var);
	//printf("EL VALOR ES %s\n\n", value);
	//free (value);
	free (var);
}

//void	expand_home(char **tokens, char *str, int i, char **env_dup)


char *grep_value(char *var, char **env)
{
    char *aux;

    if (!var)
        return (NULL);
	aux = var;
    var++;
    while(env && *env)
	{
		if (ft_strncmp(var, *env, ft_strlen(var)) == 0)
		{
			return(ft_substr(*env, ft_strlen(var) + 1, ft_strlen(*env) - (ft_strlen(var) + 1)));
		}
		env++;
	}
    free(aux);
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
    int t;

	if (!tokens || !env_dup)
		return(NULL);
    t = 0;
	while(tokens[t])
	{
		i = 0;
		while (tokens[t] && tokens[t][i] != '\0')
		{
			if (tokens[t][i] == '$' && check_var(tokens[t], i))
				expand_var(tokens, t, i, env_dup);
//			else if ((*aux)[i] == '$' && check_var(*aux, i))
//				expand_home(tokens, *aux, i, env_dup);
			i++;
		}
		t++;
	}
	return (NULL);
}
