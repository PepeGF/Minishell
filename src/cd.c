#include "../inc/minishell.h"

int cd_builtin(char **env_dup, char **cmd_splited)
{
	char    *dir;
	char	*cwd;
	char	*aux;

	if (ft_len_matrix(cmd_splited) == 1)
	{
		dir = ft_get_value_env(env_dup, "HOME");
		if (!dir)
		{
			printf("Minishell: cd: HOME not set\n");
			//cambiar por llamada a la función correcta
			return (EXIT_FAILURE);
		}
		cwd = getcwd(NULL, 0);
		aux = ft_strjoin("OLDPWD=", cwd);
		free(cwd);
		ft_replace_line_in_matrix(env_dup, aux);
		free(aux);
		free(dir);
		ft_print_matrix(env_dup);
	}
	
	return (EXIT_SUCCESS);
}

char    *ft_get_value_env(char **env_dup, char *argv)
{
	int	index_str;
	int	index_matrix;
	char	*aux;
	int		len;

	index_matrix = ft_get_index_env(env_dup, argv);
	if (index_matrix == -1)
		return (NULL);
	index_str = ft_strchr_index(env_dup[index_matrix], '=');
	len = ft_strlen(env_dup[index_matrix]);
	aux = ft_substr(env_dup[index_matrix], index_str + 1, len);
	if (!aux)
		return (NULL);
	return (aux);
}

int ft_get_index_env(char **env_dup, char *argv)
{
	int i;

	i = 0;
	if (ft_check_already_in_env(env_dup, argv) == TRUE)
	{		
		while (env_dup[i])
		{
			if (ft_strchr(env_dup[i], '=') != NULL
				&& ft_strncmp(env_dup[i], argv, ft_strlen(argv)) == 0)
				return (i);
			i++;
		}
	}
	return (-1);
}