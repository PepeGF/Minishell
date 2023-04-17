/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:45:59 by josgarci          #+#    #+#             */
/*   Updated: 2023/04/17 22:46:06 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "builtins.h"

int	export_builtin(char ***env_dup, t_list *cmd_list)
{
	int		argc;
	char	**aux;

	argc = ft_len_matrix(((t_command *)(cmd_list->content))->cmd_splited);
	if (argc == 0)
		return (0);
	if (argc > 1)
	{
		return (ft_export_with_args(env_dup, ((t_command *)(cmd_list->content)) \
		->cmd_splited));
	}
	aux = ft_sort_matrix(*env_dup);
	if (!aux)
		return (ft_memory_error());
	if (argc == 1)
		ft_print_export_alone(aux);
	ft_free_matrix(aux);
	return (0);
}

int	ft_export_with_args(char ***env_dup, char **cmd_splited)
{
	int		i;
	char	**aux;
	int		ret_value;

	i = 1;
	ret_value = SUCCESS;
	while (cmd_splited[i])
	{
		if (ft_check_valid_name_and_value(cmd_splited[i]) == 0)
		{
			if (ft_check_already_in_env(*env_dup, cmd_splited[i]) == FALSE)
			{
				aux = ft_add_line_to_matrix(env_dup, cmd_splited[i]);
				if (!aux)
					return (ret_value = ft_memory_error());
				*env_dup = aux;
			}
			else if (ft_strchr(cmd_splited[i], '=') != 0)
				ft_replace_line_in_matrix(*env_dup, cmd_splited[i]);
		}
		else
			ret_value = FAILURE;
		i++;
	}
	return (ret_value);
}

int	ft_print_export_error(char *argv)
{
	int	ret_value;

	ret_value = 1;
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(argv, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (ret_value);
}

void	ft_print_lines(char *line, int first_equal)
{
	int	j;

	j = 0;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	while (line[j])
	{
		if (j != first_equal)
			ft_putchar_fd(line[j], STDOUT_FILENO);
		else
			ft_putstr_fd("=\"", STDOUT_FILENO);
		j++;
	}
	if (first_equal != -1)
		ft_putchar_fd('\"', STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	ft_print_export_alone(char **aux)
{
	int	i;
	int	first_equal;

	i = 0;
	while (aux[i] != NULL)
	{
		if (ft_strncmp("_=", aux[i], 2) == 0)
		{
			i++;
			if (aux[i] == NULL)
				break ;
		}
		first_equal = ft_strchr_index(aux[i], '=');
		ft_print_lines(aux[i], first_equal);
		i++;
	}
}
