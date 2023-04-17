/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:46:26 by josgarci          #+#    #+#             */
/*   Updated: 2023/04/17 22:46:27 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "builtins.h"

static int	ft_print_unset_error(char *argv);
static int	ft_unset_with_argv(char ***env_dup, char **cmd_splited);
static int	ft_check_valid_name(char *argv);
static char	**ft_delete_line_from_matrix(char ***env_dup, char *argv);

int	unset_builtin(char ***env_dup, t_list *cmd_list)
{
	int		ret_value;
	char	**argv;

	if (!env_dup || !*env_dup || !cmd_list)
		return (FAILURE);
	argv = ((t_command *)(cmd_list->content))->cmd_splited;
	if (!argv || argv[1] == NULL)
		return (SUCCESS);
	ret_value = ft_unset_with_argv(env_dup, argv);
	return (ret_value);
}

int	ft_unset_with_argv(char ***env_dup, char **cmd_splited)
{
	int		i;
	int		ret_value;
	char	**aux;

	i = 1;
	ret_value = SUCCESS;
	while (cmd_splited[i])
	{
		if (ft_check_valid_name(cmd_splited[i]) == 0)
		{
			if (ft_check_already_in_env(*env_dup, cmd_splited[i]) == TRUE)
			{
				aux = ft_delete_line_from_matrix(env_dup, cmd_splited[i]);
				if (!aux)
					return (ft_memory_error());
				free(*env_dup);
				*env_dup = aux;
			}
		}
		else
			ret_value = FAILURE;
		i++;
	}
	return (ret_value);
}

char	**ft_delete_line_from_matrix(char ***matrix, char *argv)
{
	char	**aux;
	int		i;
	int		j;
	int		len_matrix;

	i = 0;
	j = 0;
	len_matrix = ft_len_matrix(*matrix);
	aux = malloc(sizeof(char *) * len_matrix);
	if (!aux)
		return (NULL);
	while ((*matrix)[i])
	{
		if (ft_strncmp((*matrix)[i], argv, ft_strlen(argv)) == 0
			&& ((*matrix)[i][ft_strlen(argv)] == '\0'
			|| (*matrix)[i][ft_strlen(argv)] == '='))
		{
			free((*matrix)[i]);
			i++;
			continue ;
		}
		aux[j++] = (*matrix)[i++];
	}
	aux[j] = NULL;
	return (aux);
}

int	ft_check_valid_name(char *argv)
{
	int	i;
	int	ret_value;

	i = 0;
	ret_value = 0;
	if (ft_isalpha(argv[0]) != TRUE && argv[0] != '_')
			ret_value = ft_print_unset_error(argv);
	i = 1;
	while (argv[i])
	{
		if (!(ft_isalnum(argv[i]) == TRUE || argv[i] == '_'))
		{
			ret_value = ft_print_unset_error(argv);
			break ;
		}
		i++;
	}
	return (ret_value);
}

int	ft_print_unset_error(char *argv)
{
	int	ret_value;

	ret_value = FAILURE;
	g_exit = EXIT_FAILURE;
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(argv, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (ret_value);
}
