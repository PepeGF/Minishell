#include "../inc/minishell.h"

int	unset_builtin(char ***env_dup, t_list *cmd_list)
{
	int i;
	int delete_count;

	if (!env_dup || !*env_dup)
		return(EXIT_FAILURE);
	if (!cmd_list || !((t_command *)(cmd_list->content))->cmd_splited)
		return(EXIT_SUCCESS);
	//contar cuántos se van a eliminar (cuántos están en env_dup)
	delete_count = ft_count_to_delete(*env_dup, ((t_command *)(cmd_list->content))->cmd_splited);

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
	i = 0;
	while ((*env_dup)[i])
	{
		i++;
	}
	return (EXIT_SUCCESS);
}

int ft_count_to_delete(char **matrix, char **cmd_splited)
{
	int i;
	int	j;
	int counter;

	while (matrix[i])
	{
		j = 0;
		while (cmd_splited[j])
		{
			j++;
		}
		i++;
	}
	
}