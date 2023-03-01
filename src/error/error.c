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

void	error_n_exit(enum e_err err, char **mem_alloc)
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
