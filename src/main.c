/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:13:37 by drontome          #+#    #+#             */
/*   Updated: 2023/02/26 19:20:27 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_command	command;
	char		**env_dup;
	char		*line;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	env_dup = ft_dup_matrix(envp);
	while (TRUE)
	{
		line = readline("minishell$>");
		if (parse(line) == NULL);
			break ;
	}
}

