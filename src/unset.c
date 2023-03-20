#include "../inc/minishell.h"

int	unset_builtin(char ***env_dup, char **cmd_splited)
{
	int		i;
	int		j;
	char	**aux;
	int		ret_value;
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
(void)env_dup;
(void)cmd_splited;
(void)aux;
(void)ret_value;
	if (!env_dup || !*env_dup)
		return(EXIT_FAILURE);
	if (!cmd_splited || cmd_splited[1] == NULL)
		return(EXIT_SUCCESS);
	ret_value = EXIT_SUCCESS;
	i = 1;

	while (cmd_splited[i])
	{
		if (ft_check_valid_name(cmd_splited[i]) == 0)
		j = 0;
		while ((*env_dup)[j])
		{

			j++;
		}
		
		i++;
	}
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