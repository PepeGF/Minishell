/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:13:37 by drontome          #+#    #+#             */
/*   Updated: 2023/04/03 14:31:38 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit;


static void	print_matrix(char **mtx)
{
	int	i;

	i = 1;
	while (mtx && *mtx)
	{
		printf("\t\t\t%d. #%s#\n", i, *mtx);
		i++;
		mtx++;
	}
	printf("\n");
}

static void	print_vars(t_vars *vars)
{
	t_list		*nodes;
	t_command	*cmd;
	int			i;

	i = 1;
	printf("EL CONTENIDO DE VARS SE MOSTRARÁ EN PANTALLA\n\n");
	/*
  printf("ENV_DUP:\n", vars->env_dup);
  print_matrix(vars->env_dup);
*/
	nodes = vars->nodes;
	while (nodes != NULL)
	{
		cmd = (t_command *)nodes->content;
		printf("COMANDO %d:\n", i);
		printf("\t\tinfile: %s\n", cmd->infile);
		printf("\t\toutfile: %s\n", cmd->outfile);
		printf("\t\tcmd_args: \n");
		print_matrix(cmd->cmd_splited);
		printf("\n");
		i++;
		nodes = nodes->next;
	}
	printf("\n");
}

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
		if (g_exit != 130)
			print_vars(&vars);
		free_nodes(&vars);
	}
	ft_free_matrix(vars.env_dup);
	exit (g_exit);
}
