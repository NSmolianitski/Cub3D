/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:59:20 by pkentaur          #+#    #+#             */
/*   Updated: 2020/11/04 13:12:18 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static size_t	my_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		++i;
	return (i);
}

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		result;
	size_t		i;
	size_t		dst_len;
	size_t		src_len;

	i = 0;
	dst_len = my_strlen(dst);
	src_len = my_strlen(src);
	result = dst_len + src_len;
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	while ((i < src_len) && (dst_len < dstsize - 1))
	{
		dst[dst_len] = src[i];
		++i;
		++dst_len;
	}
	dst[dst_len] = '\0';
	return (result);
}
