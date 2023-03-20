/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:13:19 by drontome          #+#    #+#             */
/*   Updated: 2023/01/01 12:49:45 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_n_exit(t_err err, char **mem_alloc)
{
	ft_putstr_fd("Error\n", 2);
	if (err == MEM)
	{
		perror("minishell: memory error");
		if (mem_alloc != NULL)
			ft_free_matrix(mem_alloc);
	}
	exit(EXIT_FAILURE);
}

void	p_error(t_err err, char *str)
{
	ft_putstr_fd("minishell: ", 2);
	if (err == SYN)
		ft_putstr_fd("syntax error: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return ;	
}
