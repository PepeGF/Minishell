#ifndef EXECUTOR_H
# define EXECUTOR_H
/* ************************************************************************** */
/*                                 INCLUDES                                   */
/* ************************************************************************** */
#include "minishell.h"
#include <stddef.h>
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
t_exec	init_child(t_vars *vars); int	ch_pipe_pos(t_exec *child, t_proc pos);
void	exec_error(t_exec *child, char *path);
#endif
