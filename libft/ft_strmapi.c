/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 12:15:42 by pkentaur          #+#    #+#             */
/*   Updated: 2020/11/02 15:49:58 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	if (s == 0)
		return (0);
	i = 0;
	while (s[i] != '\0')
		++i;
	str = (char*)malloc(sizeof(char) * i + 1);
	if (0 == str)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = (*f)(i, s[i]);
		++i;
	}
	str[i] = '\0';
	return (str);
}
