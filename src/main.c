/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:13:37 by drontome          #+#    #+#             */
/*   Updated: 2023/04/05 19:29:16 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_envp(char **envp);
int			g_exit;


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

/* static void	print_matrix(char **mtx)
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
} */

/* static void	print_vars(t_vars *vars)
{
	t_list		*nodes;
	t_command	*cmd;
	int			i;

	i = 1;
	printf("EL CONTENIDO DE VARS SE MOSTRARÁ EN PANTALLA\n\n");
	
  printf("ENV_DUP:\n", vars->env_dup);
  print_matrix(vars->env_dup);

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
} */

t_vars	*ft_init_varssss(char **envp)
{
	// char	**env_dup;
	t_vars	*vars;

	vars = malloc(sizeof(t_vars));
	if (!vars)
		return (NULL); //o exit(EXIT_FAILURE)
	vars->env_dup = get_envp(envp);
	vars->nodes = NULL;
	return (vars);
}

int	main(int argc, char **argv, char **envp)
{
	// char	**env_dup;
	char	**tokens;
	char	*line;
	t_vars	*vars;

	if (argc != 1 || !argv)
		return (1);
	signal(SIGQUIT, SIG_IGN);
	vars = ft_init_varssss(envp);
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
		tokens = lexer(line, vars->env_dup);
		parser(vars, tokens);
		ft_execute_builtin(vars);
		// if (g_exit != 130)
		// 	print_vars(vars);
		free_vars(vars);
	}
	ft_free_matrix(vars->env_dup);
	exit (g_exit);
}
