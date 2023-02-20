#include "../inc/minishell.h"

void	ft_delete_line_from_matrix(char ***matrix, int index)
{
	char	**aux;
	int		i;
	int		j;
	int		len_matrix;

	len_matrix = ft_matrix_len(*matrix);
	aux = malloc(sizeof(char *) * len_matrix);
	if (aux == NULL)
		return ;
	aux[len_matrix - 1] = NULL;
	i = 0;
	j = 0;
	while (i < len_matrix)
	{
		if (i != index)
		{
			aux[j] = (*matrix)[i];
			j++;
		}
		i++;
	}
	free(*matrix);
	*matrix = aux;
}

void	ft_unset_builtin(t_command cmd, t_vars *vars)
{
	(void)cmd;

	int i;
	int	index;

	i = 1;
	index = -1;
	while (cmd.comando_bonito[i])
	{
		if (ft_check_existing_variable_in_matrix(vars->env_var, cmd.comando_bonito[i], &index) == 1)
			ft_delete_line_from_matrix(&vars->env_var, index);
		if (ft_check_existing_variable_in_matrix(vars->export, cmd.comando_bonito[i], &index) == 1)
			ft_delete_line_from_matrix(&vars->export, index);
		i++;
	}
    return ;
}