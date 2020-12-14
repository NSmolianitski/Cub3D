/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:51:02 by pkentaur          #+#    #+#             */
/*   Updated: 2020/11/01 13:27:06 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int		i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (i == n)
			return (0);
		if (s1[i] != s2[i])
		{
			if ((((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]) > 0)
				return (1);
			else
				return (-1);
		}
		++i;
	}
	if (s2[i] == '\0')
		return (0);
	else
		return (-1);
}
