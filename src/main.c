/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:13:37 by drontome          #+#    #+#             */
/*   Updated: 2023/04/06 19:13:09 by josgarci         ###   ########.fr       */
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
		{
			printf("exit\n");
			break ;
		}
		signal(SIGINT, SIG_IGN);
		g_exit = 0;
		tokens = lexer(line, vars.env_dup);
		parser(&vars, tokens);
		executor(&vars);
		//ft_execute_builtin(&vars);
		free_nodes(&vars);
	}
	ft_free_matrix(vars.env_dup);
	exit (g_exit);
}
