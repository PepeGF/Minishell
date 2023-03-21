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
	int		ret_value;
	char	**argv;
(void)env_dup;
(void)ret_value;
	if (!env_dup || !*env_dup || !cmd_list)
		return(EXIT_FAILURE);
	argv = ((t_command *)(cmd_list->content))->cmd_splited;
	if (!argv || argv[1] == NULL)
		return(EXIT_SUCCESS);
	ret_value = ft_unset_with_argv(env_dup, argv);
	return (ret_value);
}

int	ft_unset_with_argv(char ***env_dup, char **cmd_splited)
{
	int		i;
	int		ret_value;
	char	**aux;

	i = 1;
	ret_value = EXIT_SUCCESS;
	while(cmd_splited[i])
	{
		if (ft_check_valid_name(cmd_splited[i]) == 0)
		{
			if (ft_check_already_in_env(*env_dup, cmd_splited[i]) == TRUE)
			{
				aux = ft_delete_line_from_matrix(env_dup, cmd_splited[i]);
				if (!aux)
					return (EXIT_FAILURE);
				free(*env_dup);
				*env_dup = aux;
			}
		}
		else
			ret_value = EXIT_FAILURE;
		i++;
	}
	return (ret_value);
}

char	**ft_delete_line_from_matrix(char ***matrix, char *argv)
{
	char	**aux;
	int		i;
	int		j;
	int		len_matrix;

	i = 0;
	j = 0;
	len_matrix = ft_len_matrix(*matrix);
	aux = malloc(sizeof(char *) * len_matrix);
	if (!aux)
		return (NULL);
	while ((*matrix)[i])
	{//int diff = ft_strncmp((*matrix)[i], argv, ft_strlen(argv));
		if (ft_strncmp((*matrix)[i], argv, ft_strlen(argv)) == 0 
			&& ((*matrix)[i][ft_strlen(argv)] == '\0' 
			|| (*matrix)[i][ft_strlen(argv)] == '='))
		{
			// printf("%s\t-->\t%s\t%d\n", (*matrix)[i], argv, diff);
			free((*matrix)[i]);
			i++;
			continue;
		}
		aux[j] = (*matrix)[i];
		i++;
		j++;
	}
	aux[j] = NULL;
	return (aux);
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