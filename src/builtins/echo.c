/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JoseGF <JoseGF@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:45:32 by josgarci          #+#    #+#             */
/*   Updated: 2023/04/19 19:24:30 by JoseGF           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "builtins.h"

static int	ft_check_n_echo(char *argv);
static void	ft_echo_no_new_line(char **cmd_splited, int fd, int index);
static void	ft_echo_with_new_line(char **cmd_splited, int fd);

int	echo_builtin(char **cmd_splited, int fd)
{
	int	i;

	if (!cmd_splited)
		return (FAILURE);
	if (cmd_splited[1] == NULL)
	{
		ft_putendl_fd("", fd);
		return (SUCCESS);
	}
	i = 1;
	while (ft_check_n_echo(cmd_splited[i]) == TRUE)
		i++;
	if (i > 1)
		ft_echo_no_new_line(cmd_splited, fd, i);
	else
		ft_echo_with_new_line(cmd_splited, fd);
	return (SUCCESS);
}

static void	ft_echo_with_new_line(char **cmd_splited, int fd)
{
	int	i;

	i = 1;
	while (cmd_splited[i])
	{
		ft_putstr_fd(cmd_splited[i], fd);
		if (cmd_splited[i + 1] != NULL)
			ft_putstr_fd(" ", fd);
		else
			ft_putendl_fd("", fd);
		i++;
	}
	return ;
}

static void	ft_echo_no_new_line(char **cmd_splited, int fd, int index)
{
	while (cmd_splited[index])
	{
		ft_putstr_fd(cmd_splited[index], fd);
		if (cmd_splited[index + 1] != NULL)
			ft_putstr_fd(" ", fd);
		index++;
	}
	return ;
}

static int	ft_check_n_echo(char *argv)
{
	int	i;
	int	len;

	if (!argv)
		return (FALSE);
	if (argv[0] != '-')
		return (FALSE);
	len = ft_strlen(argv);
	i = 1;
	while (argv[i] == 'n')
		i++;
	if (i == len)
		return (TRUE);
	return (FALSE);
}
