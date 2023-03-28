/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:32:07 by drontome          #+#    #+#             */
/*   Updated: 2023/03/27 18:27:34 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

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
		free_vars(vars);
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
	else if (cmd->outfile != NULL)
		free(cmd->outfile);
	file = rm_quotes(tokens[t]);
	if (!file)
	{
		free_vars(vars);
		error_n_exit(MEM, tokens);
	}
	else
		cmd->outfile = file;
	if (cmd->flag[APP == 1])
		cmd->flag[APP] = 0;
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
		free_vars(vars);
		error_n_exit(MEM, tokens);
	}
	else
	{
		cmd->outfile = file;
		cmd->flag[APP] = 1;
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
