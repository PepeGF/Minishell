/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:14:14 by drontome          #+#    #+#             */
/*   Updated: 2023/04/03 12:14:34 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
extern int	g_exit;

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

/*
void	sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 130;
		ft_putchar_fd('\n', STDERR_FILENO);
		ioctl(STDIN_FILENO, TIOCSTI, NULL);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
*/


