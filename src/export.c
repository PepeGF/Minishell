#include "../inc/minishell.h"


// comprobar número de argumentos

// si es solo export-> imprimir declare -x *variables entorno ordenadas = "valor" ojo con las comillas*
// si es export algo
	// comprobar si el nombre de la variable es válido
		// primer carater letra o guion bajo
		// resto caracter no caracter especial ni comillas
	// comprobar si el valor asignado es válido
	// comprobar si hay un igual en medio
int	export_builtin(char **env_dup, t_list *cmd_list, char **local_vars)//quizás t_vars vars??
{
	int	argc;
	char	**aux;
(void)local_vars;
	argc = ft_len_matrix(((t_command *)(cmd_list->content))->cmd_splited);
	if (argc == 0)//no tengo claro si hay q controlar esto
	{
		return (0);
	}
	if (argc > 1)
	{
		return (ft_export_with_args(env_dup, ((t_command *)(cmd_list->content))->cmd_splited));

	}
	aux = ft_sort_matrix(env_dup);
	if (!aux)
		return(EXIT_FAILURE);
	if (argc == 1)
	{
		// ft_print_matrix(aux);
		ft_print_export_alone(aux);
		ft_free_matrix(aux);
		return (0);
	}
	ft_free_matrix(aux);
	return (0);
}

int	ft_export_with_args(char **env_dup, char **cmd_splited)
{
	int		i;
	char	**aux;
	int		ret_value;

	i = 1;
	aux = ft_dup_matrix(env_dup);
	while (cmd_splited[i])
	{
		//chequear primer caracter de "nombre"
		ret_value = ft_check_valid_name_and_value(cmd_splited[i]);

		//comprobar si "nombre" está en aux
			//comprobar si tiene "=valor"
		//comprobar si aux[i] tiene un "="
			
		i++;
	}
	return (0);
}

int		ft_check_valid_name_and_value(char *argv)
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
		if (!((argv[i] >= 48 && argv[i] <= 57) ||
				(argv[i] >= 65 && argv[i] <= 90) ||
				argv[i] == 95 || argv[i] == 61 || 
				(argv[i] >= 97 && argv[i] <= 122)))
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
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(argv, STDERR_FILENO);
	ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
	return (ret_value);
}

void	ft_print_export_alone(char **aux)
{
	int	i;
	int	j;

	i = 0;
	while (aux[i] != NULL)
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (aux[i][j] != '=' && aux[i][j] != '\0')
		{
			ft_putchar_fd(aux[i][j], 1);
			j++;
		}
		while (aux[i][j])
		{
			ft_putchar_fd(aux[i][j], 1);
			if (aux[i][j] == '=')
				ft_putchar_fd('"', 1);
			j++;
		}
		if (ft_strchr(aux[i], '='))
			ft_putchar_fd('\"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

char	**ft_sort_matrix(char **env_dup)
{
	char	**aux;
	int		matrix_len;

	matrix_len = ft_len_matrix(env_dup);
	aux = ft_dup_matrix(env_dup);
	ft_sort_int_tab(aux, matrix_len);
	// ft_free_matrix(aux);
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
	//añadir protección !s1 || !s2, de momento no, solo va a ser usada al ordenar la matrix aux de export
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
		{
			aux = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (aux);
		}
		i++;
	}
	return (0);
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
