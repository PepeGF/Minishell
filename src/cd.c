#include "../inc/minishell.h"

int	cd_builtin(char ***env_dup, char **cmd_splited)
{
	char	*dir;
	char	buf[PATH_MAX];
	char	*aux;

	dir = ft_get_dir(env_dup, cmd_splited);
	if (!dir)
		return (EXIT_FAILURE);
	getcwd(buf, sizeof(buf));
	if (chdir(dir) != 0)
		return (EXIT_FAILURE);//error minishell: cd: "dir" No such file or directory
	else
	{
		aux = ft_strjoin("OLDPWD=", buf);
		if (ft_check_already_in_env(*env_dup, "OLDPWD") == TRUE)
			ft_replace_line_in_matrix(*env_dup, aux);
		else
			*env_dup = ft_add_line_to_matrix(env_dup, aux);
		free(aux);
		aux = ft_strjoin("PWD=", dir);
		if (ft_check_already_in_env(*env_dup, "PWD") == TRUE)
			ft_replace_line_in_matrix(*env_dup, aux);
		else
			*env_dup = ft_add_line_to_matrix(env_dup, aux);
		free(aux);
	}
	return (EXIT_SUCCESS);
}


char	*ft_get_dir(char ***env_dup, char **cmd_splited)
{
	char	*dir;

	dir = NULL;
	if (ft_len_matrix(cmd_splited) == 1)
	{
		dir = ft_get_value_env(*env_dup, "HOME");
		//print_error minishell: cd: HOME not set
		if (!dir)
			printf("minishell: cd: HOME not set\n");//esto no va aqui
	}
	else if (ft_strncmp(cmd_splited[1], "-", 2) == 0)
	{
		dir = ft_get_value_env(*env_dup, "OLDPWD");
		//print_error minishell: cd: OLDPWD not set
		if (!dir)
			printf("minishell: cd: OLDPWD not set\n");//esto no va aqui
	}
	else
		dir = cmd_splited[1];
	return (dir);		
}

/* int cd_builtin(char ***env_dup, char **cmd_splited)
{
	char    *dir;
	char	*cwd;
	char	*aux;

	if (ft_len_matrix(cmd_splited) == 1)
	{
		dir = ft_get_value_env(*env_dup, "HOME");
		if (!dir)
		{
			printf("Minishell: cd: HOME not set\n");
			//cambiar por llamada a la función correcta
			return (EXIT_FAILURE);
		}
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			//print error de cd
			return (EXIT_FAILURE);
		}
		aux = ft_strjoin("OLDPWD=", cwd);
		free(cwd);
		ft_replace_line_in_matrix(*env_dup, aux);
		free(aux);
		free(dir);
		ft_print_matrix(*env_dup);
	}
	
	return (EXIT_SUCCESS);
}
 */

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