/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:46:19 by josgarci          #+#    #+#             */
/*   Updated: 2023/04/17 22:46:21 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "builtins.h"

int	pwd_builtin(void)
{
	char	*directory;

	directory = getcwd(NULL, 0);
	if (directory)
	{
		ft_putendl_fd(directory, STDOUT_FILENO);
		free(directory);
		return (SUCCESS);
	}
	free(directory);
	g_exit = 1;
	return (FAILURE);
}
