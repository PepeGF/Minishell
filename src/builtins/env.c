/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:45:41 by josgarci          #+#    #+#             */
/*   Updated: 2023/04/18 19:29:36 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "builtins.h"

int	env_builtin(char **env_dup)
{
	int	i;

	if (env_dup == NULL)
	{
		ft_putendl_fd("minishell: env: No such file or directory",
			STDERR_FILENO);
		g_exit = 127;
		return (FAILURE);
	}
	i = 0;
	while (env_dup[i])
	{
		ft_putendl_fd(env_dup[i], STDOUT_FILENO);
		i++;
	}
	return (SUCCESS);
}
