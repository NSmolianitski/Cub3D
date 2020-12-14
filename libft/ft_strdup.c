/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 20:01:44 by pkentaur          #+#    #+#             */
/*   Updated: 2020/10/30 10:59:47 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char			*str;
	unsigned long	i;
	unsigned long	j;

	j = 0;
	while (s1[j] != '\0')
		++j;
	str = (char *)malloc(sizeof(char) * (j + 1));
	if (0 == str)
		return (0);
	else
	{
		i = 0;
		while (i < j)
		{
			str[i] = s1[i];
			++i;
		}
		str[i] = '\0';
		return (str);
	}
}
