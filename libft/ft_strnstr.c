/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:27:59 by pkentaur          #+#    #+#             */
/*   Updated: 2020/10/29 13:08:04 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static int	checkstr(size_t i, const char *haystack,
		const char *needle, size_t len)
{
	int j;

	j = 0;
	while (i <= len)
	{
		if (needle[j] == '\0')
			return (1);
		else if (haystack[i] != needle[j])
			return (0);
		++i;
		++j;
	}
	return (0);
}

static int	islonger(const char *haystack, const char *needle)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (haystack[i] != '\0')
		++i;
	while (needle[j] != '\0')
		++j;
	if (i >= j)
		return (1);
	return (0);
}

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*ptr;

	if (!islonger(haystack, needle))
		return (NULL);
	i = 0;
	ptr = (char*)haystack;
	if (needle[0] == '\0')
		return (ptr);
	while (i < len)
	{
		if (haystack[i] == needle[0])
		{
			if (checkstr(i, haystack, needle, len))
				return (ptr + i);
		}
		++i;
	}
	return (NULL);
}
