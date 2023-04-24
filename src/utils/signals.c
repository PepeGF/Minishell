/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:14:14 by drontome          #+#    #+#             */
/*   Updated: 2023/04/24 20:36:30 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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

void	sig_child(int sig)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (sig == SIGINT)
		ft_putstr_fd("\n", STDOUT_FILENO);
	else if (sig == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
}

void	wait_childs(pid_t last_cmd)
{
	int	status;

	signal(SIGINT, sig_child);
	signal(SIGQUIT, sig_child);
	waitpid(last_cmd, &status, WUNTRACED);
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			g_exit = 130;
		else if (WTERMSIG(status) == SIGQUIT)
			g_exit = 131;
	}
	while (waitpid(-1, NULL, WUNTRACED) > 0)
		continue ;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
