#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/wait.h>//para linux funcion wait
# include <sys/param.h>
# include <string.h>

# define TRUE 1
# define FALSE 0
//no hay nada preparado para $_ (el último comando utilizado, se guarda en las variables de entorno)

// typedef struct s_data
// {
// 	int					num_cmds;
// 	int					num_pipes;
// 	int					last_code;
// 	struct s_command	*cmd_list;
// 	char				**envp_copy;
// 	char				**export;
// }	t_data;

typedef struct s_command
{
	char	**cmd_splited;
	int		fd[2];
	char	**heredocs;
	char	**appends;
	struct s_command	*prev;
}	t_command;

typedef struct s_vars
{
	struct s_command	*cmd_list;
	char	**env_dup;
	char	**local_vars;

}	t_vars;



char	**smart_split(char *s);
char	*parser(char *line);

t_list	*hardcoded(char **env_dup);
void    free_cmd_list(t_list *cmd_list);
void	wololo();


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

int		unset_builtin(char ***env_dup, t_list *cmd_list);




#endif

