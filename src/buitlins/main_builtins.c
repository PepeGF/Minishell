/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:13:37 by drontome          #+#    #+#             */
/*   Updated: 2023/04/04 11:10:29 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_shlvl(char **env_dup);

void sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		// rl_replace_line("", 0);
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
	env_dup = ft_dup_matrix(envp);
	ft_set_shlvl(env_dup);
	cmd_list = hardcoded(env_dup);
	// printf("******* VARIABES DE ENTORNO ANTES DE UNSET ********\n");
	// printf("%p->direccion de meoria de env_dup\n", env_dup);
	// ft_print_matrix(env_dup);
	// printf("\n\nRESULTADO: %d\n\n",unset_builtin(&env_dup, cmd_list));
	// printf("******* VARIABES DE ENTORNO despues DE UNSET ********\n");
	// printf("%p->direccion de meoria de env_dup\n", env_dup);
	// ft_print_matrix(env_dup);

	// ft_print_matrix(((t_command *)(cmd_list->content))->cmd_splited);
	echo_builtin(((t_command *)(cmd_list->content))->cmd_splited, STDOUT_FILENO);
	// cd_builtin(&env_dup, ((t_command *)(cmd_list->content))->cmd_splited);
	// ft_print_matrix(env_dup);
	// export_builtin(&env_dup, cmd_list);
	ft_free_matrix(env_dup);
	free_cmd_list(cmd_list);
	return (0);
}

void	ft_set_shlvl(char **env_dup)
{
	char	*shlvl;
	char	*aux;
	int		level;

	aux = ft_get_value_env(env_dup, "SHLVL");
	if (aux != NULL)
	{
		level = ft_atoi(aux);
		if (level != 0)
			level++;
		else
			level = 1;
		shlvl = ft_itoa(level);
		free(aux);
		aux = ft_strjoin("SHLVL=", shlvl);
		free(shlvl);
		ft_replace_line_in_matrix(env_dup, aux);
		free(aux);
	}
	else
	{
		return ;
	}
}
