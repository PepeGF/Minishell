/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:20:11 by josgarci          #+#    #+#             */
/*   Updated: 2023/04/23 19:36:27 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
/* ************************************************************************** */
/*                                 INCLUDES                                   */
/* ************************************************************************** */
# include "minishell.h"
# include <stddef.h>
/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */
typedef struct s_exec
{
	t_command	*cmd;
	int			pipe_in[2];
	int			pipe_out[2];
	char		**env_dup;
	char		**paths;
	size_t		n_proc;
	size_t		tot_pr;
	pid_t		last_cmd;
}			t_exec;
/* ************************************************************************** */
/*                                   ENUMS                                    */
/* ************************************************************************** */
typedef enum e_pipe
{
	RD,
	WR,
}			t_pipe;

typedef enum e_proc
{
	FIRST,
	MID,
	LAST,
	UNQ,
}			t_proc;
/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */
t_proc	check_pos(size_t pos, size_t tot);
t_exec	init_child(t_vars *vars);
int		ch_pipe_pos(t_exec *child, t_proc pos);
void	close_fd(t_exec *child);
void	exec_error(t_exec *child, char *path);
void	wait_childs(pid_t last_cmd);

///////////////////////////// PATH AUX FUNCTIONS ///////////////////////////////
char	**get_paths(char **envp);
char	*ft_get_right_path(t_exec *child);

/////////////////////////////// CHILD FUNCTIONS ////////////////////////////////
void	redirect_fd(t_command *cmd, int *fd_in, int *fd_out);
int		fork_child(t_exec *child);

/////////////////////////////// CHILD FUNCTIONS ////////////////////////////////

void	ft_execve_child_to_vars(t_exec *child);
void	ft_child(t_exec *child);
int		pipe_child(t_exec *child, t_command *cmd);
void	execution_with_child(t_list *aux, t_vars *vars);
void	run_child(t_exec *child);

#endif
