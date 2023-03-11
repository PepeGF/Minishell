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
	t_list		*cmd_list;
	char		**env_dup;
	// char		*line;

	if (argc != 1 || !argv)
		return (1);
	envp = (char **)envp;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	env_dup = ft_dup_matrix(envp);
	/* while (TRUE)
	{
		line = readline("minishell$>");
		if (parser(line) == NULL)
			break ;
	} */
	cmd_list = hardcoded(env_dup);
	/* exit status - variable error = */ //pwd_builtin();
	// wololo();
	/* exit status - variable error = */ //env_builtin(env_dup);
	// free(line);
	/* exit status - variable error = */ export_builtin(env_dup, cmd_list);
	ft_free_matrix(env_dup);
	return (0);
}

