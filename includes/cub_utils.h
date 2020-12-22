/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:58:24 by pkentaur          #+#    #+#             */
/*   Updated: 2020/12/22 15:58:30 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_CUB_UTILS_H
# define CUB3D_CUB_UTILS_H

# include "libft.h"

void	*s_calloc(size_t count, size_t size, char c);
int		lst_find_longest(t_list *lst_begin);
int		cub_strcpy(char *dst, char *src);
int		cub_strcmp(const char *s1, const char *s2);
void	strprint(const char *str, int output);
void	print_error(char *error);
int		skip_spaces(const char *line, int i);
int		skip_spaces_and_commas(const char *line, int i);
void	double_close(int fd1, int fd2);
void	check_err(int *i, char *line);

#endif
