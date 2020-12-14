/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 11:10:39 by pkentaur          #+#    #+#             */
/*   Updated: 2020/11/12 18:03:22 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static int	count_strs_length(char const *s1, char const *s2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
		++i;
	while (s2[j] != '\0')
		++j;
	return (i + j);
}

char		*gnl_strjoin(char *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (s1 == 0)
		return (0);
	str = (char*)malloc(sizeof(char) * (count_strs_length(s1, s2) + 1));
	i = 0;
	if (0 == str)
		return (0);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		++i;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		++i;
		++j;
	}
	str[i] = '\0';
	return (str);
}

char		*gnl_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return ((char*)s + i);
		++i;
	}
	if (c == '\0')
		return ((char*)s + i);
	return (0);
}

char		*gnl_strdup(const char *s1)
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
