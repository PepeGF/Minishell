/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:32:07 by drontome          #+#    #+#             */
/*   Updated: 2023/04/23 12:30:10 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <fcntl.h>

static void	create_file(char *file, int app);

void	get_infile(t_vars *vars, char **tokens, int t)
{
	t_command	*cmd;
	char		*file;

	cmd = (t_command *)ft_lstlast(vars->nodes)->content;
	if (cmd->infile != NULL && access(cmd->infile, R_OK) != 0)
		return ;
	else if (cmd->infile != NULL && cmd->flag[HER] == 1)
	{
		unlink(cmd->infile);
		free(cmd->infile);
		cmd->flag[HER] = 0;
	}
	else if (cmd->infile != NULL)
		free(cmd->infile);
	file = rm_quotes(tokens[t]);
	if (!file)
	{
		free_nodes(vars);
		error_n_exit(MEM, tokens);
	}
	else
		cmd->infile = file;
}

void	get_outfile(t_vars *vars, char **tokens, int t)
{
	t_command	*cmd;
	char		*file;

	cmd = (t_command *)ft_lstlast(vars->nodes)->content;
	if (cmd->outfile != NULL && access(cmd->outfile, F_OK) == 0
		&& access(cmd->outfile, W_OK) != 0)
		return ;
	else if (cmd->infile != NULL && access(cmd->infile, F_OK) == 0
		&& access(cmd->infile, R_OK) != 0)
		return ;
	else if (cmd->outfile != NULL)
		free(cmd->outfile);
	file = rm_quotes(tokens[t]);
	if (!file)
	{
		free_nodes(vars);
		error_n_exit(MEM, tokens);
	}
	else
	{
		if (cmd->flag[APP] == 1)
			cmd->flag[APP] = 0;
		create_file(file, cmd->flag[APP]);
		cmd->outfile = file;
	}
}

void	get_append(t_vars *vars, char **tokens, int t)
{
	t_command	*cmd;
	char		*file;

	cmd = (t_command *)ft_lstlast(vars->nodes)->content;
	if (cmd->outfile != NULL && access(cmd->outfile, F_OK) == 0
		&& access(cmd->outfile, W_OK) != 0)
		return ;
	else if (cmd->outfile != NULL)
		free(cmd->outfile);
	file = rm_quotes(tokens[t]);
	if (!file)
	{
		free_nodes(vars);
		error_n_exit(MEM, tokens);
	}
	else
	{
		cmd->flag[APP] = 1;
		create_file(file, cmd->flag[APP]);
		cmd->outfile = file;
	}
}

int	get_redir(char **tokens, int t, t_vars *vars)
{
	int	len;

	len = ft_strlen(tokens[t]);
	if (len > 2 || !is_redir(tokens[t], tokens[t]))
		return (FALSE);
	else if (len == 1 && tokens[t][0] == '<')
		get_infile(vars, tokens, ++t);
	else if (len == 1 && tokens[t][0] == '>')
		get_outfile(vars, tokens, ++t);
	else if (len == 2 && ft_strncmp(tokens[t], ">>", len) == 0)
		get_append(vars, tokens, ++t);
	else if (len == 2 && ft_strncmp(tokens[t], "<<", len) == 0)
		get_heredoc(vars, tokens, ++t);
	else
		return (FALSE);
	return (TRUE);
}

static void	create_file(char *file, int app)
{
	int	fd;

	if (!file)
		return ;
	if (app == 1)
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd >= 0)
		close(fd);
}
