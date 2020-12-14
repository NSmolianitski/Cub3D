/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:36:19 by pkentaur          #+#    #+#             */
/*   Updated: 2020/11/02 15:26:09 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

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

char		*ft_strjoin(char const *s1, char const *s2)
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
