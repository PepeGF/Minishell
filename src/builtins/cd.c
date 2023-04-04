#include "../inc/minishell.h"

char	*ft_quitar_lineas1(char *str, char *buf, char ***env_dup);
char	*ft_quitar_lineas2(char *str, char *dir, char ***env_dup);

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
		aux = ft_quitar_lineas1("OLDPWD=", buf, env_dup);
		free(aux);
		getcwd(buf, sizeof(buf));
		aux = ft_quitar_lineas2("PWD=", buf, env_dup);
		free(aux);

printf("buffff->>>>\t%s\n", buf);
	}
	return (EXIT_SUCCESS);
}

char	*ft_quitar_lineas1(char *str, char *buf, char ***env_dup)
{
	char	*aux;

	aux = ft_strjoin(str, buf);
	if (ft_check_already_in_env(*env_dup, str) == TRUE)
		ft_replace_line_in_matrix(*env_dup, aux);
	else
		*env_dup = ft_add_line_to_matrix(env_dup, aux);
	return (aux);
}

char	*ft_quitar_lineas2(char *str, char *dir, char ***env_dup)
{
	char	*aux;

	aux = ft_strjoin(str, dir);
	if (ft_check_already_in_env(*env_dup, str) == TRUE)
		ft_replace_line_in_matrix(*env_dup, aux);
	else
		*env_dup = ft_add_line_to_matrix(env_dup, aux);
	return (aux);
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

char	*ft_get_value_env(char **env_dup, char *argv)
{
	int		index_str;
	int		index_matrix;
	char	*aux;
	int		len;

	index_matrix = ft_get_index_env(env_dup, argv);
	if (index_matrix == -1)
		return (NULL);
	index_str = ft_strchr_index(env_dup[index_matrix], '=');
	len = ft_strlen(env_dup[index_matrix]);
	aux = ft_substr(env_dup[index_matrix], index_str + 1, len);
	if (!aux || ft_strlen(aux) == 0)
		return (NULL);
	return (aux);
}

int	ft_get_index_env(char **env_dup, char *argv)
{
	int	i;

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