/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:13:37 by drontome          #+#    #+#             */
/*   Updated: 2023/03/16 19:39:40 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler(int sig);
static char	**get_envp(char **envp);

int	main(int argc, char **argv, char **envp)
{
	char		**env_dup;
	char		*line;
	// t_command	command;

	if (argc != 1 || !argv)
		return (1);
//	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	env_dup = get_envp(envp);
	while (TRUE)
	{
		line = readline("Minishell$> ");
		if (line == NULL)
			break ;
		lexer(line, env_dup);
		free(line);
	}
	ft_free_matrix(env_dup);
}

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

static char	**get_envp(char **envp)
{
	char	**env_dup;

	if (envp == NULL)
		return (NULL);
	env_dup = ft_dup_matrix(envp);
	if (!env_dup)
		error_n_exit(MEM, NULL);
	return (env_dup);
}
