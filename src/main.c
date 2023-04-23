/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:13:37 by drontome          #+#    #+#             */
/*   Updated: 2023/04/23 12:27:53 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit;

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	char	**tokens;
	char	*line;

	if (argc != 1 || !argv)
		exit (EXIT_FAILURE);
	init_vars(&vars, envp);
	while (TRUE)
	{
		signal(SIGINT, sig_handler);
		line = readline("Minishell$> ");
		if (line == NULL)
			break ;
		signal(SIGINT, SIG_IGN);
		tokens = lexer(line, vars.env_dup);
		if (!tokens)
			continue ;
		g_exit = 0;
		if (parser(&vars, tokens) == 0)
			executor(&vars);
		update_vars(&vars);
	}
	free_nodes(&vars);
	printf("exit\n");
	exit (g_exit);
}
