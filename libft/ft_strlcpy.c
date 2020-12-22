/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:03:03 by pkentaur          #+#    #+#             */
/*   Updated: 2020/11/02 16:23:26 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	if (src == 0)
		return (0);
	if (src[0] == '\0')
	{
		dst[0] = '\0';
		return (0);
	}
	i = 0;
	j = 0;
	while (src[i] != '\0')
		++i;
	++i;
	while (j < dstsize && j < i)
	{
		dst[j] = src[j];
		++j;
	}
	dst[--j] = '\0';
	return (i - 1);
}
