#include "../inc/minishell.h"
/* static const struct s_builtins	g_builtins[] = {
	{"echo", echo_builtin},
	{"cd", cd_builtin},
	{"pwd", pwd_builtin},
	{"env", env_builtin},
	{"export", export_builtin},
	{"unset", unset_builtin},
	{NULL, NULL}
} */

//esta declaración según está cumple norma, pero no se si el g_ es correcto.
static char	g_builtins[7][7] = {
	"pwd",
	"env",
	"export",
	"unset",
	"echo",
	"cd",
{}
};

void	wololo()
{
	int i = 0;
	while (i <= 6)
	{
		printf("%s\n", g_builtins[i]);
		i++;
	}
}

int	pwd_builtin()
{
	char	*directory;

	directory = getcwd(NULL, 0);
	if (directory)
	{
		ft_putendl_fd(directory, STDOUT_FILENO);
		free(directory);
		return (0);
	}
	free(directory);
	//si hay error directory == NULL, en ese caso
	//establecer valor de error (no consigo que el original falle)
	//perror("mensaje de error")
	return (EXIT_FAILURE);
}

int	env_builtin(char **env_dup)
{
	int	i;

	if (env_dup == NULL)
	{
		//print error
		ft_putendl_fd("Minishell: env: No such file or directory", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (env_dup[i])
	{
		ft_putendl_fd(env_dup[i], STDERR_FILENO);
		i++;
	}
	return (0);
}

int	export_builtin(char **env_dup, t_list *cmd_list)//quizás t_vars vars??
{
	int	argc;
	char	**aux;
	int	i = 0;
	int	j;

	argc = ft_len_matrix(((t_command *)(cmd_list->content))->cmd_splited);
	if (argc == 0)//no tengo claro si hay q controlar esto
	{
		return (0);
	}
	aux = ft_sort_matrix(env_dup);
	if (!aux)
		return(EXIT_FAILURE);
	if (argc == 1)
	{
		// ft_print_matrix(aux);
		ft_print_export_alone(aux);
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
	return (0);
		//imprimir matriz env, con los prefijos, las colmillas de valores y ordenado
		//ordenar aux

		//imprimir declare -x y nombre="valor"
	}
// comprobar número de argumentos

// si es solo export-> imprimir declare -x *variables entorno ordenadas = "valor" ojo con las comillas*
// si es export algo
	// comprobar si el nombre de la variable es válido
		// primer carater letra o guion bajo
		// resto caracter no caracter especial ni comillas
	// comprobar si el valor asignado es válido
	// comprobar si hay un igual en medio

	ft_free_matrix(aux);
	return (0);
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