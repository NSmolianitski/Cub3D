/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:29:11 by pkentaur          #+#    #+#             */
/*   Updated: 2020/11/01 12:45:03 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;

	if ((dst == 0 && src == 0) || len == 0)
		return (dst);
	i = 0;
	if (src > dst)
	{
		while (i < len)
		{
			((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
			++i;
		}
	}
	else
	{
		--len;
		while (i < len)
		{
			((unsigned char*)dst)[len] = ((unsigned char*)src)[len];
			--len;
		}
		((unsigned char*)dst)[len] = ((unsigned char*)src)[0];
	}
	return (dst);
}
