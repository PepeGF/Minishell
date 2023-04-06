/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:37:08 by drontome          #+#    #+#             */
/*   Updated: 2023/03/28 12:34:16 by drontome         ###   ########.fr       */
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
	t_list	*nodes;
	char	**env_dup;
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
void		parser(t_vars *vars, char **tokens);
//////////////////////////////////INIT_UTILS////////////////////////////////////
void		init_vars(t_vars *vars, char **envp);
t_command	*init_cmd(void);
void		init_nodes(t_vars *vars, char **tokens);
void		free_nodes(t_vars *vars);
void		free_cmd(void *content);
////////////////////////////////////UTILS///////////////////////////////////////
int			is_inquotes(char *str, char *var, char *qu);
int			is_redir(char *str, char *op);
void		sig_handler(int sig);
////////////////////////////////////ERRORS//////////////////////////////////////
void		error_n_exit(enum e_err err, char **mem_alloc);
void		p_error(t_err err, char c, char *str);
void		here_error(char *lim);

int		pwd_builtin();
int		env_builtin(char **env_dup);

int		export_builtin(char ***env_dup, t_list *cmd_list);
char	**ft_sort_matrix(char **env_dup);
void	ft_sort_int_tab(char **tab, int size);
int		ft_strcmp(char *s1, char *s2);
void	ft_print_matrix(char **matrix);//esta debería ir a la libft
int		ft_strchr_index(const char *s, int c);//esta tb
void	ft_print_export_alone(char **aux);
int		ft_export_with_args(char ***env_dup, char **cmd_splited);
int		ft_check_valid_name_and_value(char *argv);
int		ft_print_export_error(char *argv);
int		ft_check_already_in_env(char **env_dup, char *argv);
char	**ft_add_line_to_matrix(char ***matrix, char *argv);
int		ft_replace_line_in_matrix(char **matrix, char *argv);

int		unset_builtin(char ***env_dup,  t_list *cmd_list);
int		ft_check_valid_name(char *argv);
int		ft_print_unset_error(char *argv);
int		ft_unset_with_argv(char ***env_dup, char **cmd_splited);
char	**ft_delete_line_from_matrix(char ***env_dup, char *argv);

int		echo_builtin(char **cmd_splited, int fd);

int 	cd_builtin(char ***env_dup, char **cmd_splited);
char    *ft_get_value_env(char **env_dup, char *argv);
int		ft_get_index_env(char **env_dup, char *argv);
char	*ft_get_dir(char ***env_dup, char **cmd_splited);


#endif
