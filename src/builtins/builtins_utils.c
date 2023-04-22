/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:45:08 by josgarci          #+#    #+#             */
/*   Updated: 2023/04/17 22:45:11 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "builtins.h"

int	ft_check_valid_name_and_value(char *argv)
{
	int	i;
	int	ret_value;

	i = 0;
	ret_value = 0;
	if (ft_isalpha(argv[0]) != 1 && argv[0] != '_')
			ret_value = ft_print_export_error(argv);
	i = 1;
	while (argv[i] != '=')
	{
		if (!(ft_isalnum(argv[i]) == 1 || argv[i] == '_'))
			return (ft_print_export_error(argv));
		i++;
	}
	return (ret_value);
}

int	ft_check_already_in_env(char **env_dup, char *argv)
{
	int	i;
	int	len_argv;
	int	diff;

	if (!env_dup || !argv)
		return (FALSE);
	i = 0;
	len_argv = ft_strlen(argv);
	while (env_dup[i])
	{
		if (ft_strchr_index(argv, '=') == -1)
		{
			diff = ft_strncmp(env_dup[i], argv, len_argv);
			if (diff == 0 && env_dup[i][len_argv] == '=')
				return (TRUE);
		}
		else
		{
			diff = ft_strncmp(env_dup[i], argv, ft_strchr_index(argv, '=') + 1);
			if (diff == 0)
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

char	**ft_add_line_to_matrix(char ***matrix, char *argv)
{
	int		i;
	int		len_matrix;
	char	**aux;

	if (!matrix || !*matrix || !argv)
		return (NULL);
	len_matrix = ft_len_matrix(*matrix);
	i = 0;
	aux = malloc(sizeof(char *) * (len_matrix + 2));
	if (!aux)
		return (NULL);
	aux[len_matrix + 1] = NULL;
	while ((*matrix)[i])
	{
		aux[i] = (*matrix)[i];
		i++;
	}
	aux[len_matrix] = ft_strdup(argv);
	free(*matrix);
	return (aux);
}

int	ft_replace_line_in_matrix(char **matrix, char *argv)
{
	int	i;
	int	index;

	if (!matrix || !argv)
		return (FAILURE);
	i = 0;
	while (matrix[i])
	{
		index = ft_strchr_index(argv, '=');
		if (ft_strncmp(matrix[i], argv, index + 1) == 0)
		{
			free(matrix[i]);
			matrix[i] = ft_strdup(argv);
			if (!matrix[i])
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
