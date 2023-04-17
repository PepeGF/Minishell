#include "../inc/minishell.h"
#include "builtins.h"

int	ft_sort_error(void)
{
	g_exit = 12;
	perror(NULL);
	return (FAILURE);
}

int	export_builtin(char ***env_dup, t_list *cmd_list)//quizás t_vars vars??
{
	int		argc;
	char	**aux;

	argc = ft_len_matrix(((t_command *)(cmd_list->content))->cmd_splited);
	if (argc == 0)
		return (0);
	if (argc > 1)
	{
		return (ft_export_with_args(env_dup, ((t_command *)(cmd_list->content)) \
		->cmd_splited));
	}
	aux = ft_sort_matrix(*env_dup);
	if (!aux)
		return (ft_sort_error());
	if (argc == 1)
		ft_print_export_alone(aux);
	ft_free_matrix(aux);
	return (0);
}

int	ft_export_with_args(char ***env_dup, char **cmd_splited)
{
	int		i;
	char	**aux;
	int		ret_value;

	i = 1;
	ret_value = EXIT_SUCCESS;
	while (cmd_splited[i])
	{
		if (ft_check_valid_name_and_value(cmd_splited[i]) == 0)
		{
			if (ft_check_already_in_env(*env_dup, cmd_splited[i]) == FALSE)
			{
				aux = ft_add_line_to_matrix(env_dup, cmd_splited[i]);
				if (!aux)
					return (ret_value = EXIT_FAILURE);
				*env_dup = aux;
			}
			else if (ft_strchr(cmd_splited[i], '=') != 0)
				ft_replace_line_in_matrix(*env_dup, cmd_splited[i]);
		}
		else
			ret_value = EXIT_FAILURE;
		i++;
	}
	return (ret_value);
}

int	ft_replace_line_in_matrix(char **matrix, char *argv)
{
	int	i;
	int	index;

	if (!matrix || !argv)
		return (EXIT_FAILURE);
	i = 0;
	while (matrix[i])
	{
		index = ft_strchr_index(argv, '=');
		if (ft_strncmp(matrix[i], argv, index + 1) == 0)
		{
			free(matrix[i]);
			matrix[i] = ft_strdup(argv);
			if (!matrix[i])
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

char	**ft_add_line_to_matrix(char ***matrix, char *argv)
{
	int		i;
	int		len_matrix;
	char	**aux;

	if (!matrix || !*matrix || !argv)
		return (NULL);
	len_matrix = ft_len_matrix(*matrix);
	i = 0;
	aux = malloc(sizeof(char *) * (len_matrix + 2));
	if (!aux)
		return (NULL);
	aux[len_matrix + 1] = NULL;
	while ((*matrix)[i])
	{
		aux[i] = (*matrix)[i];
		i++;
	}
	aux[len_matrix] = ft_strdup(argv);
	free(*matrix);
	return (aux);
}

int	ft_check_already_in_env(char **env_dup, char *argv)
{
	int	i;
	int	len_argv;
	int	diff;

	if (!env_dup || !argv)
		return (FALSE);
	i = 0;
	len_argv = ft_strlen(argv);
	while (env_dup[i])
	{
		if (ft_strchr_index(argv, '=') == -1)
		{
			diff = ft_strncmp(env_dup[i], argv, len_argv);
			if (diff == 0 && env_dup[i][len_argv] == '=')
				return (TRUE);
		}
		else
		{
			diff = ft_strncmp(env_dup[i], argv, ft_strchr_index(argv, '=') + 1);
			if (diff == 0)
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int	ft_check_valid_name_and_value(char *argv)
{
	int	i;
	int	ret_value;

	i = 0;
	ret_value = 0;
	if (ft_isalpha(argv[0]) != 1 && argv[0] != '_')
			ret_value = ft_print_export_error(argv);
	i = 1;
	while (argv[i])
	{
		if (!(ft_isalnum(argv[i]) == 1 || argv[i] == '_' || argv[i] == '='))
		{
			ret_value = ft_print_export_error(argv);
			break ;
		}
		i++;
	}
	return (ret_value);
}

int	ft_print_export_error(char *argv)
{
	int	ret_value;

	ret_value = 1;
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(argv, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (ret_value);
}

void	ft_print_lines(char *line, int first_equal)
{
	int	j;

	j = 0;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	while (line[j])
	{
		if (j != first_equal)
			ft_putchar_fd(line[j], STDOUT_FILENO);
		else
			ft_putstr_fd("=\"", STDOUT_FILENO);
		j++;
	}
	if (first_equal != -1)
		ft_putchar_fd('\"', STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	ft_print_export_alone(char **aux)
{
	int	i;
	int	j;
	int	first_equal;

	i = 0;
	while (aux[i] != NULL)
	{
		if (ft_strncmp("_=", aux[i], 2) == 0)
		{
			i++;
			if (aux[i] == NULL)
				break ;
		}
		j = 0;
		first_equal = ft_strchr_index(aux[i], '=');
		ft_print_lines(aux[i], first_equal);
		i++;
	}
}

char	**ft_sort_matrix(char **env_dup)
{
	char	**aux;
	int		matrix_len;

	matrix_len = ft_len_matrix(env_dup);
	aux = ft_dup_matrix(env_dup);
	if (!aux)
		return (NULL);
	ft_sort_int_tab(aux, matrix_len);
	return (aux);
}

void	ft_sort_int_tab(char **tab, int size)
{
	int		index;
	int		counter;
	char	*temp;

	counter = 0;
	while (counter < size)
	{
		index = 0;
		while (index < size - 1)
		{
			if (ft_strcmp(tab[index], tab[index + 1]) > 0)
			{
				temp = tab[index];
				tab[index] = tab[index + 1];
				tab[index + 1] = temp;
			}
			index++;
		}
		counter++;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	aux;

	i = 0;
	if (!s1 || !s2)
		return (EXIT_FAILURE);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
		{
			aux = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (aux);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	ft_print_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		ft_putendl_fd(matrix[i], STDOUT_FILENO);
		i++;
	}
	return ;
}

int	ft_strchr_index(const char *s, int c)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] != '\0' && s[i] != (unsigned char)c)
		i++;
	if (s[i] == (unsigned char)c)
		return (i);
	return (-1);
}
