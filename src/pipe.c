# include "../inc/minishell.h"



void	ft_close_pipes(t_command *cmd)
{
	t_command	*aux;

	aux = cmd;
	while (aux->next)
	{
		close(aux->fd[0]);
		close(aux->fd[1]);
		aux = aux->next;
	}
	return ;
}

void	ft_dup_infile(t_command *cmd)
{
	int	fd_infile;
	int	i;

	if (cmd->infiles == NULL)
		return ;
	i = 0;
	while(cmd->infiles[i])
	{
		fd_infile = open(cmd->infiles[i], O_RDONLY);
		if (fd_infile < 0)
			perror("fdinfile");//pendiente de mejora
		if (cmd->infiles[i + 1] != NULL)
		{
			dup2(fd_infile, 0);
			close(fd_infile);
		}
		close(fd_infile);
		//gestionar "<<" here-doc
		i++;
	}
}

void	ft_dup_outfile(t_command *cmd)
{
	int	fd_outfile;
	int	i;

	if (cmd->outfiles == NULL)
		return ;
	i = 0;
	while(cmd->outfiles[i])
	{
		fd_outfile = open(cmd->outfiles[i], O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (fd_outfile < 0)
			perror("fd_outfile:");//pendiente de mejora
		if (cmd->outfiles[i + 1] == NULL)
		{
			close(STDOUT_FILENO);
			dup(fd_outfile);
		}
		close(fd_outfile);
		//gestionar ">>" appends
		i++;
	}
}

void	ft_redirections(t_command *cmd)
{
	if (cmd->prev != NULL)
		dup2(cmd->prev->fd[0], 0);
	if (cmd->next != NULL)
		dup2(cmd->fd[1], 1);
	ft_dup_infile(cmd);
	ft_dup_outfile(cmd);
}