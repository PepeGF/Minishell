# include "../inc/minishell.h"


void	ft_free_array(char **envp_copy)
{
	int	i;

	if (envp_copy == NULL)
		return ;
	i = 0;
	while (envp_copy[i])
	{
		free(envp_copy[i]);
		i++;
	}
	free(envp_copy);
}

void	ft_free_list(t_command *lst)
{
	t_command	*aux;
	t_command	*aux2;

	aux = lst;
	while (aux)
	{
		aux2 = aux->next;
		free(aux);
		aux = aux2;
	}
}

t_command	**ft_copy_enviroment_vars_into_list(t_command **env_copy, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_lstadd_back_mod(env_copy, ft_lstnew_mod((void *)envp[i]));
		i++;
	}
	//esto hay que liberarlo
	return (0);
}

void	ft_print_command(t_command *env_copy)
{
	t_command *aux;
	int i = 0;

	aux = env_copy;
	while (aux->next)
	{
		i++;
		// printf("%d - %s\n", i, (char *)(aux->content));
		aux = aux->next;
	}
	// printf("%d - %s\n", ++i, (char *)(aux->content));
}

