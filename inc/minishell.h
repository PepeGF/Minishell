/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:37:08 by drontome          #+#    #+#             */
/*   Updated: 2023/04/23 19:42:09 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                                 INCLUDES                                   */
/* ************************************************************************** */
# include "../libft/inc/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/param.h>
# include <sys/wait.h>
# include <unistd.h>
# include <termios.h>
/* ************************************************************************** */
/*                                  DEFINES                                   */
/* ************************************************************************** */
# define RED "\033[0;91m"
# define GREEN "\033[0;32m"
# define CEND "\033[0;39m"
# define TRUE 1
# define FALSE 0
/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */
typedef struct s_vars
{
	t_list			*nodes;
	char			**env_dup;
	struct termios	settings;
}			t_vars;

typedef struct s_command
{
	char	**cmd_splited;
	char	*infile;
	char	*outfile;
	int		flag[2];
}			t_command;

/* ************************************************************************** */
/*                                   ENUMS                                    */
/* ************************************************************************** */
typedef enum e_err
{
	MEM,
	SYN,
	QU,
	FD,
}			t_err;

typedef enum e_flag
{
	HER,
	APP,
}			t_flag;

/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */
char		**lexer(char *line, char **env_dup);
char		**expander(char **tokens, char **env_dup);
int			parser(t_vars *vars, char **tokens);
void		executor(t_vars *vars);
//////////////////////////////////INIT_UTILS////////////////////////////////////
void		init_vars(t_vars *vars, char **envp);
t_command	*init_cmd(void);
void		init_nodes(t_vars *vars, char **tokens);
void		update_vars(t_vars *vars);
////////////////////////////////////UTILS///////////////////////////////////////
int			is_inquotes(char *str, char *var, char *qu);
int			is_redir(char *str, char *op);
void		free_nodes(t_vars *vars);
void		free_cmd(void *content);
void		sig_handler(int sig);
void		sig_child(int sig);
void		wait_childs(pid_t last_cmd);
////////////////////////////////////ERRORS//////////////////////////////////////
void		error_n_exit(enum e_err err, char **mem_alloc);
int			p_error(t_err err, char c, char *str);
void		here_error(char *lim);
//////////////////////////////////BUILTINS//////////////////////////////////////
int			ft_memory_error(void);
int			ft_execute_builtin(t_vars *vars);
char		*ft_get_value_env(char **env_dup, char *argv);
int			ft_replace_line_in_matrix(char **matrix, char *argv);
char		**ft_add_line_to_matrix(char ***matrix, char *argv);

#endif
