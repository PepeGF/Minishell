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