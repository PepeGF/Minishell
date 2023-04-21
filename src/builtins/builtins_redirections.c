#include "../inc/minishell.h"
#include "builtins.h"

static int	ft_perror(void);

int	ft_redirect_out(t_command *cmd, int *stdout_fd)
{
	int	fd_out;

	*stdout_fd = dup(STDOUT_FILENO);
	if (cmd->flag[APP] == 1)
		fd_out = open(cmd->outfile, O_WRONLY | O_APPEND | O_CREAT);
	else
		fd_out = open(cmd->outfile, O_WRONLY | O_CREAT);
	if (fd_out < 0)
		return (ft_perror());
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (ft_perror());
	if (close(fd_out) == 1)
		return (ft_perror());
	return (SUCCESS);
}

int	ft_redirect_builtins(t_command *cmd, int *stdout_fd, int *stdin_fd)
{
	int	fd_in;

	if (cmd->outfile != NULL)
		return (ft_redirect_out(cmd, stdout_fd));
	if (cmd->infile != NULL)
	{
		*stdin_fd = dup(STDIN_FILENO);
		fd_in = open(cmd->infile, O_RDONLY);
		if (fd_in < 0)
			return (ft_perror());
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (ft_perror());
		if (close(fd_in) == 1)
			return (ft_perror());
	}
	return (SUCCESS);
}

int	ft_recorver_std_fd(t_command *cmd, int std_fd[2])
{
	if (cmd->outfile != NULL)
	{
		if (dup2(std_fd[1], STDOUT_FILENO) == -1)
			return (ft_perror());
		if (close(std_fd[1]))
			return (ft_perror());
	}
	if (cmd->infile != NULL)
	{
		if (dup2(std_fd[0], STDIN_FILENO) == -1)
			return (ft_perror());
		if (close(std_fd[0]))
			return (ft_perror());
	}
	return (SUCCESS);
}

static int	ft_perror(void)
{
	perror("minishell");
	return (FAILURE);
}
