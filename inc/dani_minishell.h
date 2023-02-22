/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dani_minishell.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:22:22 by drontome          #+#    #+#             */
/*   Updated: 2023/02/22 19:55:56 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_prompt
{
	t_list	*cmds;
	char	**envp;

}				t_prompt;
#endif
