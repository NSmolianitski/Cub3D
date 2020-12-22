/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 11:11:03 by pkentaur          #+#    #+#             */
/*   Updated: 2020/11/11 16:01:53 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 200
# endif

# include <stdlib.h>

int		get_next_line(int fd, char **line);
char	*gnl_strjoin(char *s1, char const *s2);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strdup(const char *s1);

#endif
