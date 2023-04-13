/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:32:07 by drontome          #+#    #+#             */
/*   Updated: 2023/03/27 18:34:49 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static char	*fill_heredoc(char *lim);
static int	get_fd(char **file);
static void	free_n_close(char *line, char *lim, int fd);
static void	false_heredoc(t_vars *vars, char **tokens, int t);
extern int	g_exit;

void	get_heredoc(t_vars *vars, char **tokens, int t)
{
	t_command	*cmd;
	char		*lim;

	cmd = (t_command *)ft_lstlast(vars->nodes)->content;
	if (cmd->infile != NULL && access(cmd->infile, R_OK) != 0)
		return (false_heredoc(vars, tokens, t));
	else if (cmd->infile != NULL && cmd->flag[HER] == 1)
	{
		unlink(cmd->infile);
		free(cmd->infile);
		cmd->flag[HER] = 0;
	}
	else if (cmd->infile != NULL)
		free(cmd->infile);
	lim = rm_quotes(tokens[t]);
	if (!lim)
	{
		free_nodes(vars);
		error_n_exit(MEM, tokens);
	}
	cmd->infile = fill_heredoc(lim);
	cmd->flag[HER] = 1;
}

static char	*fill_heredoc(char *lim)
{
	char	*file;
	char	*line;
	int		fd;

	fd = get_fd(&file);
	if (fd < 0)
	{
		if (file)
			free(file);
		return (NULL);
	}
	line = NULL;
	signal(SIGINT, sig_handler);
	while (TRUE)
	{
		line = readline("> ");
		if (g_exit == 130 || !line || (ft_strncmp(line, lim, ft_strlen(lim)) \
			== 0 && ft_strlen(line) == ft_strlen(lim)))
			break ;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	free_n_close(line, lim, fd);
	return (file);
}

static int	get_fd(char **file)
{
	int		fd;
	int		num;
	char	*temp;

	fd = -1;
	num = 0;
	temp = NULL;
	while (fd < 0 && num < 100)
	{
		if (temp)
			free(temp);
		temp = ft_strdup(".temp_minishell_");
		temp = ft_strjoin_free(temp, ft_itoa(num));
		if (temp != NULL)
			fd = open(temp, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
		num++;
	}
	if (fd >= 0)
		*file = temp;
	else
	{
		free(temp);
		*file = NULL;
	}
	return (fd);
}

static void	false_heredoc(t_vars *vars, char **tokens, int t)
{
	char	*lim;
	char	*line;

	lim = rm_quotes(tokens[t]);
	line = NULL;
	if (!lim)
	{
		free_nodes(vars);
		error_n_exit(MEM, tokens);
	}
	signal(SIGINT, sig_handler);
	while (TRUE)
	{
		line = readline("> ");
		if (g_exit == 130 || !line || (ft_strncmp(line, lim, ft_strlen(lim)) \
			== 0 && ft_strlen(line) == ft_strlen(lim)))
			break ;
		free(line);
	}
	free_n_close(line, lim, -1);
}

static void	free_n_close(char *line, char *lim, int fd)
{
	signal(SIGINT, SIG_IGN);
	if (!line && g_exit != 130)
		here_error(lim);
	else if (line)
		free(line);
	if (lim)
		free(lim);
	if (fd >= 0)
		close(fd);
}
