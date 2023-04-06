/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:13:37 by drontome          #+#    #+#             */
/*   Updated: 2023/04/06 19:02:58 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_set_shlvl(char ***env_dup);
int			g_exit;


static char	**get_envp(char **envp)
{
	char	**env_dup;

	if (envp == NULL)
		return (NULL);
	env_dup = ft_dup_matrix(envp);
	ft_set_shlvl(&env_dup);
	if (!env_dup)
		error_n_exit(MEM, NULL);
	return (env_dup);
}
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
		ft_execute_builtin(&vars);
		if (g_exit != 130)
			print_vars(&vars);
		free_nodes(&vars);
	}
	ft_free_matrix(vars.env_dup);
	exit (g_exit);
}

static void	ft_set_shlvl(char ***env_dup)
{
	char	*shlvl;
	char	*aux;
	int		level;
	char	**env_aux;

	aux = ft_get_value_env(*env_dup, "SHLVL");
	if (aux != NULL)
	{
		level = ft_atoi(aux) + 1;
		shlvl = ft_itoa(level);
		free(aux);
		aux = ft_strjoin("SHLVL=", shlvl);
		free(shlvl);
		ft_replace_line_in_matrix(*env_dup, aux);
		free(aux);
	}
	else
	{
		env_aux = ft_add_line_to_matrix(env_dup, "SHLVL=1");
		*env_dup = env_aux;
	}
}