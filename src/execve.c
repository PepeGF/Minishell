# include "../inc/minishell.h"

char	*path_string_from_env_copy(char **envp)
{
	int		i;
	char	*path_value;
	int		len_path;

	i = 0;
	while (envp[i])
	{
		//q pasa si no hay variable PATH, eso no está gestionado
		if (!ft_strncmp("PATH=", envp[i], 5))
		{ 
			break;
		}
		i++;
	}
	if (envp[i] == NULL)
	{
		printf("NO HAY VARIABLE PATH PUTO INUTIL\n");
		return (NULL);
	}
	len_path = ft_strlen(envp[i]);
	path_value = ft_substr(envp[i], (unsigned int)i - 1, len_path - i + 1);
	return (path_value);
}

void	ft_each_path_with_final_slash(char **each_path)
{
	int		i;
	char	*aux;

	i = 0;
	while (each_path[i])
	{
		aux = each_path[i];
		each_path[i] = ft_strjoin(each_path[i], "/");
		free(aux);
		i++;
	}
	return ;
}

void	ft_each_path_with_user_arg(char **each_path, char *arg)
{
	int		i;
	char	*aux;

	i = 0;
	while (each_path[i])
	{
		aux = each_path[i];
		each_path[i] = ft_strjoin(each_path[i], arg);
		free (aux);
		// printf("%s\n", each_path[i]);
		i++;
	}
}

char	*ft_get_path_to_execve(char **envp, char *arg)
{
	int 	i;
	char	*path_value;
	char	**each_path_in_PATH;
	char	*accesible_path;

	i = 0;
	path_value = path_string_from_env_copy(envp);
	if (path_value)
	{
			each_path_in_PATH = ft_split(path_value, ':');
			free (path_value);
			ft_each_path_with_final_slash(each_path_in_PATH);
			ft_each_path_with_user_arg(each_path_in_PATH, arg);
		while (each_path_in_PATH[i])
		{
			if (!access(each_path_in_PATH[i], X_OK))
			{
				accesible_path = ft_strdup(each_path_in_PATH[i]);
				ft_free_array(each_path_in_PATH);
				return (accesible_path);
			}
			i++;
		}
		ft_free_array(each_path_in_PATH);
	}
	return (NULL);	//no se si esto tan simple dará problemas al liberar
}

void	ft_execute(char *path_to_execve, char **args, char **envp_copy)
{
	if (path_to_execve == NULL)
	{
		if (ft_strchr(args[0], '/'))
		{
			if (!access(args[0], X_OK))
			{
				execve(args[0], args, envp_copy);
			}
			else
			{
				execve(args[0], args, envp_copy);
				perror("minishell");
			}			
		}
		else
			ft_putstr_fd("minishell: command not found\n", 2);
	}
	else
		execve(path_to_execve, args, envp_copy);
}


//find linea de PATH
	//recortar desde el primer =
	//split en :
	//iterar en split[i] el access
		//si alguno da 0->mandar al hijo y execve
		//si ninguno da 0->comprobar ruta instroducida por el usuario
			//si no access -> ft_putstr_fd(2, "minishell: command not found\n", 29) ¿Desde hijo?
			//si accsess -> mandar al hijo y execve
