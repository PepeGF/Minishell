/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:13:37 by drontome          #+#    #+#             */
/*   Updated: 2023/02/28 20:58:43 by drontome         ###   ########.fr       */
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
	// t_command	command;
	char		**env_dup;
	char		*line;

	if (argc != 1 || !argv)
		return (1);
	envp = (char **)envp;
//	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	env_dup = ft_dup_matrix(envp);
	if (env_dup == NULL)
		error_n_exit(MEM, NULL);
	while (TRUE)
	{
		line = readline("minishell$>");
		if (line == NULL)
			break ;
		parser(line); 
		free(line);
	}
	ft_free_matrix(env_dup);
}

