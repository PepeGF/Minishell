#include <stdio.h>
#include <unistd.h>
#include "../libft/libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srclen;

	i = 0;
	srclen = ft_strlen(src);
	if (dstsize == 0)
		return (srclen);
	while (src[i] && i < (dstsize - 1) && dstsize != 0)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	lens1;

	lens1 = ft_strlen(s1);
	ptr = (char *)malloc(sizeof(char) * (lens1 + 1));
	if (ptr == NULL)
		return (0);
	ft_strlcpy(ptr, s1, lens1 + 1);
	return (ptr);
}

int	ft_matrix_len(char **matrix)
{
	int	i;

	if (matrix == NULL)
		return (0);
	i = 0;
	while (matrix[i])
	{
		i++;
	}
	return (i);
}

void	ft_print_matrix(char **matrix, int fd)
{
	int i;
(void)fd;
	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		printf("%d\t%s\n", i, matrix[i]);
        free(matrix[i]);
		i++;
	}
    free(matrix);
	return ;
}

void	ft_delete_line_index_from_matrix(char ***matrix, int index)
{
	char	**aux;
	int		i;
	int		j;
	int		len_matrix;

	len_matrix = ft_matrix_len(*matrix);
	aux = malloc(sizeof(char *) * len_matrix);
	if (aux == NULL)
		return ;
	aux[len_matrix - 1] = NULL;
	i = 0;
	j = 0;
	while (i < len_matrix)
	{
		if (i != index)
		{   
			aux[j] = ft_strdup((*matrix)[i]);
			j++;
		}
		i++;
	}
    free(*matrix);
	*matrix = aux;
}

void leaks(void)
{
    system("leaks -fullContent --list a.out");
}
int main(int argc, char *argv[])
{
    atexit(leaks);
    int i = 0;
    char **aux;
    aux = malloc(sizeof (char *) * argc);
    aux[argc] = NULL;
    while (argv[i])
    {
        aux[i] = argv[i];
        i++;
    }
    int index = 1;
    ft_delete_line_index_from_matrix(&aux, index);
    ft_print_matrix(aux, 1);

    return (0);
}