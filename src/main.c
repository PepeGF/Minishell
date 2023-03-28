/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:13:37 by drontome          #+#    #+#             */
/*   Updated: 2023/03/27 17:29:44 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

static void	sig_handler(int sig);
static char	**get_envp(char **envp);
int			g_exit;

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
	char	**env_dup;
	char	**tokens;
	char	*line;
	t_vars	*vars;

	if (argc != 1 || !argv)
		return (1);
	//	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	while (TRUE)
	{
		env_dup = get_envp(envp);
		line = readline("Minishell$> ");
		if (line == NULL)
			break ;
		tokens = lexer(line, env_dup);
		//free (line);
		vars = parser(tokens, env_dup);
		print_vars(vars);
		free_vars(vars);
	}
	ft_free_matrix(env_dup);
}
