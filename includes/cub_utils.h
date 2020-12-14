#ifndef CUB3D_CUB_UTILS_H
#define CUB3D_CUB_UTILS_H

#include "libft.h"

void	double_free(char **str1, char **str2);
void	*s_calloc(size_t count, size_t size, char c);
int		lst_find_longest(t_list *lst_begin);
int		cub_strcpy(char *dst, char *src);
int		cub_strcmp(const char *s1, const char *s2);
void	strprint(const char *str, int output);
void	print_error(char *error);
int		skip_spaces(const char *line, int i);
int		skip_spaces_and_commas(const char *line, int i);
void	double_close(int fd1, int fd2);
int		cub_abs(int num);

#endif
