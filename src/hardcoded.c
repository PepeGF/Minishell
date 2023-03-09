#include "minishell.h"

void    hardcoded(char **env_dup)
{
	(void)env_dup;
	t_list  *cmd_list;
	t_command *cmd;

	cmd_list = malloc(sizeof(t_list));
	cmd = malloc(sizeof(t_command));

	cmd_list->next = NULL;
	cmd_list->content = (void *)cmd;

	cmd->cmd_splited = ft_split("pwd", ' ');
	cmd->fd[0] = 0;
	cmd->fd[1] = 1;
	cmd->heredocs = ft_split("", ' ');
	cmd->appends = ft_split("", ' ');

	printf("%s\n", ((t_command *)(cmd_list->content))->cmd_splited[0]);

	free_cmd_list(cmd_list)
	return ;
}

void    free_cmd_list(t_list *cmd_list)
{
	int i;

	if (!cmd_list)
		return ;
	while (cmd_list)
	{
		i = 0;
		while (cmd_list->cmd_splited[i])
		{
			free(cmd_list->cmd_splited[i])
			i++;
		}
		cmd_list = cmd_list->next;
	}
	return ;
}