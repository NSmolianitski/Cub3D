/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:13:40 by pkentaur          #+#    #+#             */
/*   Updated: 2020/11/04 16:18:47 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	i;

	str = (char*)malloc(count * size);
	if (0 == str)
		return (0);
	i = 0;
	while (i < count * size)
	{
		str[i] = 0;
		++i;
	}
	return ((void*)str);
}
