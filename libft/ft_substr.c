/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:26:13 by pkentaur          #+#    #+#             */
/*   Updated: 2020/11/02 16:50:04 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static unsigned int	my_strlen(const char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
		++i;
	return (i);
}

char				*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (s == 0)
		return (0);
	if (start >= my_strlen(s))
	{
		str = (char*)malloc(sizeof(char));
		if (0 == str)
			return (0);
		str[0] = '\0';
		return (str);
	}
	str = (char*)malloc(sizeof(char) * (len + 1));
	i = 0;
	if (0 == str)
		return (0);
	while (i < len)
	{
		str[i] = s[start + i];
		++i;
	}
	str[i] = '\0';
	return (str);
}
