/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:01:43 by pkentaur          #+#    #+#             */
/*   Updated: 2020/11/01 13:05:34 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;

	i = 0;
	while (i != n)
	{
		if (((unsigned char*)s1)[i] != ((unsigned char*)s2)[i])
		{
			if (((unsigned char*)s1)[i] - ((unsigned char*)s2)[i] > 0)
				return (((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]);
			else if (((unsigned char*)s1)[i] - ((unsigned char*)s2)[i] < 0)
				return (((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]);
		}
		++i;
	}
	return (0);
}
