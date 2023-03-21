#include "minishell.h"

void    free_cmd_list(t_list *cmd_list);

t_list    *hardcoded(char **env_dup)
{
	(void)env_dup;
	t_list  *cmd_list;
	t_command *cmd;

	cmd_list = malloc(sizeof(t_list));
	cmd = malloc(sizeof(t_command));

	cmd_list->next = NULL;
	cmd_list->content = (void *)cmd;

	cmd->cmd_splited = ft_split("unset ZZZ YYY XXX Z y AAA", ' ');
	cmd->fd[0] = 0;
	cmd->fd[1] = 1;
	cmd->heredocs = ft_split("", ' ');
	cmd->appends = ft_split("", ' ');

	// printf("%s\n\n", ((t_command *)(cmd_list->content))->cmd_splited[0]);

	return (cmd_list);
}

void    free_cmd_list(t_list *cmd_list)
{
	t_list	*aux;

	if (!cmd_list)
		return ;
	while (cmd_list)
	{
		ft_free_matrix(((t_command *)(cmd_list->content))->cmd_splited);
		ft_free_matrix(((t_command *)(cmd_list->content))->heredocs);
		ft_free_matrix(((t_command *)(cmd_list->content))->appends);
		free(cmd_list->content);
		aux = cmd_list->next;
		free(cmd_list);
		cmd_list = aux;
	}
	return ;
}