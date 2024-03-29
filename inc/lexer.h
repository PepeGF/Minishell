/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:37:08 by drontome          #+#    #+#             */
/*   Updated: 2023/03/28 11:38:54 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
/* ************************************************************************** */
/*                                 INCLUDES                                   */
/* ************************************************************************** */
# include <unistd.h>
/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */
char	**smart_split(char *s);
char	**redir_split(char **tokens);
int		check_syntax(char **tokens);
int		is_app_or_her(char *str, char *red);
size_t	count_newtokens(char **tokens);

#endif
