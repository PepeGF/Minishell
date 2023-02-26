#include "../inc/minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;
	char *line;
	//char *wololo;

	line = readline("Minishell: ");
	//wololo = ft_strjoin("Hola ", "que tal");
	//printf("%s\n", wololo);
	rl_clear_history();
	
	return (0);
}



