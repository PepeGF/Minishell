# include "../inc/minishell.h"

void	ft_error_exit(char *err_msg)
{
	printf("%s\n", err_msg);
	perror("");
	exit(EXIT_FAILURE);
}

void leaks ()
{
	system ("leaks -fullContent --list minishell");
}

void	ft_free_nodes(t_command *cmd)
{
	t_command	*aux;

	aux = cmd;
	while (aux)
	{
		free(aux->comando_a_pelo);
		// free(aux->comando_con_flags);
		ft_free_array(aux->comando_bonito);
		ft_free_array(aux->infiles);
		ft_free_array(aux->outfiles);
		aux = aux->next;
	}
}

void		ft_preliminar_check(int argc, char *argv[])
{
	(void)argv;

	if (argc > 1)
	{
		ft_putstr_fd("Usage: ./minishell\n", 1);
		exit(EXIT_SUCCESS);
	}
}

int	ft_strchr_index(char *str, char c)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_env_var_key_len(char *env_var)
{
	int	i;

	if (!env_var)
		return (-1);
	i = 0;
	while (env_var[i])
	{
		if (env_var[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

void	ft_print_matrix(char **matrix, int fd)
{
	int i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		ft_putnbr_fd(i, fd);
		ft_putstr_fd("\t", fd);
		ft_putendl_fd(matrix[i], fd);
		i++;
	}
	return ;
}

int	ft_matrix_len(char **matrix)
{
	int	i;

	if (matrix == NULL)
		return (0);
	i = 0;
	while (matrix[i])
	{
		i++;
	}
	return (i);
}