/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:37:08 by drontome          #+#    #+#             */
/*   Updated: 2023/03/28 12:06:34 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */
int		get_redir(char **tokens, int t, t_vars *vars);
void	get_heredoc(t_vars *vars, char **tokens, int t);
int		get_pipe(char **tokens, int t, t_vars *vars);
int		get_arg(char *arg, t_vars *vars);
char	*rm_quotes(char *str);

#endif
