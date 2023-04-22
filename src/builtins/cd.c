/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:45:18 by josgarci          #+#    #+#             */
/*   Updated: 2023/04/17 22:45:20 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "builtins.h"

static int	ft_set_directories(char *buf, char ***env_dup, char *dir);
static char	*ft_get_dir(char ***env_dup, char **cmd_splited);
static int	ft_get_index_env(char **env_dup, char *argv);

int	cd_builtin(char ***env_dup, char **cmd_splited)
{
	char	*dir;
	char	buf[PATH_MAX];

	dir = ft_get_dir(env_dup, cmd_splited);
	if (!dir)
		return (FAILURE);
	getcwd(buf, sizeof(buf));
	if (chdir(dir) != 0)
		return (ft_chdir_error(dir));
	else
		return (ft_set_directories(buf, env_dup, dir));
}

int	ft_set_directories(char *buf, char ***env_dup, char *dir)
{
	char	*aux;
	char	temp[PATH_MAX];

	aux = ft_strjoin("OLDPWD=", buf);
	if (!aux)
		return (ft_join_error(dir));
	if (ft_check_already_in_env(*env_dup, "OLDPWD") == TRUE)
		ft_replace_line_in_matrix(*env_dup, aux);
	else
		*env_dup = ft_add_line_to_matrix(env_dup, aux);
	free(aux);
	if (getcwd(temp, sizeof(temp)) == NULL)
		return (ft_getcwd_error(dir));
	aux = ft_strjoin("PWD=", dir);
	if (!aux)
		return (ft_join_error(dir));
	if (ft_check_already_in_env(*env_dup, "PWD=") == TRUE)
		ft_replace_line_in_matrix(*env_dup, aux);
	else
		*env_dup = ft_add_line_to_matrix(env_dup, aux);
	free(aux);
	free(dir);
	return (SUCCESS);
}

char	*ft_get_dir(char ***env_dup, char **cmd_splited)
{
	char	*dir;

	dir = NULL;
	if (ft_len_matrix(cmd_splited) == 1)
	{
		dir = ft_get_value_env(*env_dup, "HOME");
		if (!dir)
		{
			g_exit = EXIT_FAILURE;
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		}
	}
	else if (ft_strncmp(cmd_splited[1], "-", 2) == 0)
	{
		dir = ft_get_value_env(*env_dup, "OLDPWD");
		if (!dir)
		{
			g_exit = EXIT_FAILURE;
			ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
		}
	}
	else
		dir = ft_strdup(cmd_splited[1]);
	return (dir);
}

char	*ft_get_value_env(char **env_dup, char *argv)
{
	int		index_str;
	int		index_matrix;
	char	*aux;
	int		len;

	index_matrix = ft_get_index_env(env_dup, argv);
	if (index_matrix == -1)
		return (NULL);
	index_str = ft_strchr_index(env_dup[index_matrix], '=');
	len = ft_strlen(env_dup[index_matrix]);
	aux = ft_substr(env_dup[index_matrix], index_str + 1, len);
	if (!aux || ft_strlen(aux) == 0)
		return (NULL);
	return (aux);
}

int	ft_get_index_env(char **env_dup, char *argv)
{
	int	i;

	i = 0;
	if (ft_check_already_in_env(env_dup, argv) == TRUE)
	{		
		while (env_dup[i])
		{
			if (ft_strchr(env_dup[i], '=') != NULL
				&& ft_strncmp(env_dup[i], argv, ft_strlen(argv)) == 0)
				return (i);
			i++;
		}
	}
	return (-1);
}
