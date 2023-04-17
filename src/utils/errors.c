/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:13:19 by drontome          #+#    #+#             */
/*   Updated: 2023/03/20 12:22:20 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
extern int g_exit;

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

void	p_error(t_err err, char c, char *str)
{
	g_exit = 2;
	ft_putstr_fd("minishell: ", 2);
	if (err == SYN)
		ft_putstr_fd("syntax error near unexpected token `", 2);
	else if (err == QU)
		ft_putstr_fd("error while looking for matching `", 2);
	if (c != 0)
		ft_putchar(c);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return ;
}

void	here_error(char *lim)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("warning: here-document delimited by end-of-file ", 2);
	ft_putstr_fd("(wanted `", 2);
	if (lim)
		ft_putstr_fd(lim, 2);
	ft_putstr_fd("\')\n", 2);
}

void	exec_error(char *str, char *path)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	if (path)
		free(path);
	exit(127);
}