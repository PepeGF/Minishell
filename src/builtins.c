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

int	export_builtin(char **env_dup)
{
// comprobar número de argumentos
// si es solo export-> imprimir declare -x *variables entorno ordenadas = "valor" ojo con las comillas*
// si es export algo
	// comprobar si el nombre de la variable es válido
		// primer carater letra o guion bajo
		// resto caracter no caracter especial ni comillas
	// comprobar si el valor asignado es válido
	// comprobar si hay un igual en medio


	return (0);
}