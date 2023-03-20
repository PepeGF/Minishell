#include "../inc/minishell.h"

//comprobar si los caracteres son válidos 0-9,a-z,_,A_Z
	//comprobar si nombre está en env_dup
		//si no, salir con SUCCESS
		//si está -> eliminar:
			//encontrar el index en env_dup
			//crear aux con lenmatrix= len - 1
			//poner nulo al final
			//recorrer env_dup
				//si no es el index copiar a aux
			//liberar env_dup
			//apuntar env_dup a aux
int	unset_builtin(char ***env_dup,  t_list *cmd_list)
{
	char	**aux;
	int		ret_value;
	char	**argv;
(void)env_dup;
(void)aux;
(void)ret_value;
	if (!env_dup || !*env_dup || !cmd_list)
		return(EXIT_FAILURE);
	argv = ((t_command *)(cmd_list->content))->cmd_splited;
	if (!argv || argv[1] == NULL)
	{
		if (argv[1] == NULL)
			printf("SOLO HAS METIDO UNSET\n");
		return(EXIT_SUCCESS);
	}
	ret_value = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}

int	ft_check_valid_name(char *argv)
{
	int	i;
	int	ret_value;

	i = 0;
	ret_value = 0;
	if (ft_isalpha(argv[0]) != 1 && argv[0] != '_')
			ret_value = ft_print_unset_error(argv);
	i = 1;
	while (argv[i])
	{
		if (!(ft_isalnum(argv[i]) == 1 || argv[i] == '_'))
		{
			ret_value = ft_print_unset_error(argv);
			break ;
		}
		i++;
	}
	return (ret_value);
}

int	ft_print_unset_error(char *argv)
{
	int	ret_value;

	ret_value = 1;
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(argv, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (ret_value);
}