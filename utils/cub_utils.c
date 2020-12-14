#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

void	double_free(char **str1, char **str2)
{
	free(*str1);
	free(*str2);
}

void	double_close(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

int		cub_strcpy(char *dst, char *src)
{
	int		src_len;
	int		i;

	src_len = ft_strlen(src);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		++i;
	}
	return (i);
}

void	*s_calloc(size_t count, size_t size, char c)
{
	char	*str;
	size_t	i;

	str = (char*)malloc(sizeof(char) * (count * size + 1));
	if (0 == str)
		return (0);
	i = 0;
	while (i < count * size)
	{
		str[i] = c;
		++i;
	}
	str[i] = '\0';
	return ((void*)str);
}

int	lst_find_longest(t_list *lst_begin)
{
	int		max_strlen;
	int		cur_strlen;

	max_strlen = 0;
	while (lst_begin)
	{
		cur_strlen = ft_strlen(lst_begin->content);
		if (cur_strlen > max_strlen)
			max_strlen = cur_strlen;
		lst_begin = lst_begin->next;
	}
	return (max_strlen);
}