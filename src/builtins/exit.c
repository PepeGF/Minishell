/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:45:51 by josgarci          #+#    #+#             */
/*   Updated: 2023/04/20 23:06:29 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "builtins.h"

static int	ft_isnumber(char *str);
static int	ft_exit_error_no_number(char *str);
static int	ft_exit_with_arg(char *str);

int	exit_builtin(char **cmd_splitted)
{
	if (cmd_splitted[1] != NULL && ft_isnumber(cmd_splitted[1]) == FALSE)
	{
		exit (ft_exit_error_no_number(cmd_splitted[1]));
	}
	if (ft_len_matrix(cmd_splitted) > 2)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		g_exit = 255;
		return (FAILURE);
	}
	if (ft_len_matrix(cmd_splitted) == 2)
	{
		if (ft_isnumber(cmd_splitted[1]) == FALSE)
			exit (ft_exit_error_no_number(cmd_splitted[1]));
		else
			exit (ft_exit_with_arg(cmd_splitted[1]));
	}
	else
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit (EXIT_SUCCESS);
	}
}

int	ft_isnumber(char *str)
{
	int	i;

	if (!str)
		return (FALSE);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_exit_error_no_number(char *str)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	g_exit = 255;
	exit(g_exit);
}

int	ft_exit_with_arg(char *str)
{
	int	num;

	num = ft_atoi(str) % 256;
	if (num < 0)
		num = 256 + num;
	g_exit = num;
	ft_putendl_fd("exit", STDOUT_FILENO);
	return (num);
}
