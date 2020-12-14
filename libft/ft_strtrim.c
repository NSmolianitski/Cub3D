/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:01:11 by pkentaur          #+#    #+#             */
/*   Updated: 2020/11/05 12:09:15 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	trim_start(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = -1;
	while (s1[i] != '\0')
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
			{
				k = i;
				break ;
			}
			++j;
		}
		if (k == -1)
			return (0);
		else if (k != i)
			return (k + 1);
		++i;
	}
	return (k + 1);
}

static int	trim_end(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (s1[i] != '\0')
		++i;
	k = i + 1;
	while (i >= 0)
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (s1[i - 1] == set[j])
			{
				k = i;
				break ;
			}
			++j;
		}
		if (k != i)
			return (k - 2);
		--i;
	}
	return (k - 2);
}

static int	is_empty_or_full(char const *s1, char const *set)
{
	int		i;
	int		j;

	if (s1[0] == '\0')
		return (1);
	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
				break ;
			++j;
		}
		if (set[j] == '\0')
			return (0);
		++i;
	}
	return (1);
}

static void	swapper(int *arr, char *str, char const *s1)
{
	while (arr[0] != arr[2] + 1)
	{
		str[arr[1]] = s1[arr[0]];
		arr[0] += 1;
		arr[1] += 1;
	}
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		arr[3];

	if (s1 == 0)
		return (0);
	if (is_empty_or_full(s1, set))
	{
		str = (char*)malloc(sizeof(char));
		if (0 == str)
			return (0);
		str[0] = '\0';
		return (str);
	}
	arr[0] = trim_start(s1, set);
	arr[2] = trim_end(s1, set);
	str = (char*)malloc(sizeof(char) * (arr[2] - arr[0] + 2));
	arr[1] = 0;
	if (0 == str)
		return (0);
	swapper(arr, str, s1);
	str[arr[1]] = '\0';
	return (str);
}
