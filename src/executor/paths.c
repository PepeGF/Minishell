/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 13:20:48 by josgarci          #+#    #+#             */
/*   Updated: 2023/04/23 13:20:51 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "builtins.h"

static void	add_slash(char **paths);

char	*ft_get_right_path(t_exec *child)
{
	int		i;
	char	*path;

	if (!child || child->paths == NULL)
		return (NULL);
	i = 0;
	while (child->paths[i])
	{
		path = ft_strjoin(child->paths[i], child->cmd->cmd_splited[0]);
		if (path == NULL)
			i++;
		else if (access(path, X_OK) != 0)
		{
			free(path);
			i++;
		}
		else
			return (path);
	}
	return (NULL);
}

char	**get_paths(char **envp)
{
	char	*path_var;
	char	**paths;

	path_var = NULL;
	while (!path_var && envp && *envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			path_var = *envp;
		envp++;
	}
	if (!path_var)
		return (NULL);
	paths = ft_split(ft_strchr(path_var, '=') + 1, ':');
	add_slash(paths);
	return (paths);
}

static void	add_slash(char **paths)
{
	char	*temp;
	int		i;

	temp = NULL;
	i = 0;
	while (paths[i])
	{
		temp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		if (temp)
			free(temp);
		temp = NULL;
		i++;
	}
	return ;
}
