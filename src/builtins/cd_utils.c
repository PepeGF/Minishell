/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:45:25 by josgarci          #+#    #+#             */
/*   Updated: 2023/04/17 22:45:27 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "builtins.h"

int	ft_getcwd_error(char *dir)
{
	perror("minishell");
	free(dir);
	g_exit = EXIT_FAILURE;
	return (FAILURE);
}

int	ft_join_error(char *dir)
{
	perror(NULL);
	free(dir);
	g_exit = 12;
	return (FAILURE);
}

int	ft_chdir_error(char *dir)
{
	perror("minishell: cd");
	g_exit = EXIT_FAILURE;
	free(dir);
	return (FAILURE);
}
