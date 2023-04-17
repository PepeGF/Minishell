#ifndef BUILTINS_H
# define BUILTINS_H

extern int	g_exit;

/* ************************************************************************** */
/*                                   ENUMS                                    */
/* ************************************************************************** */

typedef enum e_builtins
{
	PWD,
	CD,
	EXPORT,
	UNSET,
	ENV,
	ECHO,
	EXIT,
	NONE,
}			t_builtins;

typedef enum e_returns
{
	SUCCESS,
	FAILURE,
}			t_returns;
/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */
int		ft_check_builtin(char **cmd_splitted);

//////////////////////////////////// EXPORT ////////////////////////////////////
int		export_builtin(char ***env_dup, t_list *cmd_list);
void	ft_print_export_alone(char **aux);
char	**ft_sort_matrix(char **env_dup);
void	ft_sort_int_tab(char **tab, int size);
int		ft_export_with_args(char ***env_dup, char **cmd_splited);

///////////////////////////////////// PWD //////////////////////////////////////
int		pwd_builtin(void);

///////////////////////////////////// ENV //////////////////////////////////////
int		env_builtin(char **env_dup);

/////////////////////////////// BUILTINS UTILS /////////////////////////////////
int		ft_check_valid_name_and_value(char *argv);
int		ft_check_already_in_env(char **env_dup, char *argv);
char	**ft_add_line_to_matrix(char ***matrix, char *argv);
int		ft_replace_line_in_matrix(char **matrix, char *argv);

int		ft_strcmp(char *s1, char *s2);
void	ft_print_matrix(char **matrix);//esta debería ir a la libft
int		ft_strchr_index(const char *s, int c);//esta tb
int		ft_print_export_error(char *argv);

//////////////////////////////////// UNSET /////////////////////////////////////
int		unset_builtin(char ***env_dup, t_list *cmd_list);

///////////////////////////////////// ECHO /////////////////////////////////////
int		echo_builtin(char **cmd_splited, int fd);

////////////////////////////////////// CD //////////////////////////////////////
int		cd_builtin(char ***env_dup, char **cmd_splited);
char	*ft_get_value_env(char **env_dup, char *argv);
int		ft_getcwd_error(char *dir);
int		ft_join_error(char *dir);
int		ft_chdir_error(char *dir);


///////////////////////////////////// EXIT /////////////////////////////////////
int		exit_builtin(char **cmd_splitted);

#endif