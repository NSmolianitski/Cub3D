/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:02:48 by pkentaur          #+#    #+#             */
/*   Updated: 2020/11/14 15:58:53 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void		free_mem(char **strarr, int words)
{
	int		i;

	i = 0;
	while (i < words)
	{
		if (0 == strarr[i])
			break ;
		free(strarr[i++]);
	}
	free(strarr);
}

static int		write_words(char const *s, char c, int *arr, char **result)
{
	while (s[++arr[0]])
		if (s[arr[0]] == c && (s[arr[0] + 1] != c || s[arr[0] + 1] != '\0'))
			arr[3] = arr[0] + 1;
		else if (s[arr[0]] != c && (s[arr[0] + 1] == c
					|| s[arr[0] + 1] == '\0'))
			if (!(result[arr[2]++] = ft_substr(s, arr[3], arr[0] - arr[3] + 1)))
			{
				free_mem(result, arr[1]);
				return (0);
			}
	return (1);
}

char			**ft_split(char const *s, char c)
{
	char	**result;
	int		arr[4];

	if (0 == s)
		return (0);
	arr[0] = -1;
	arr[1] = 0;
	while (s[++arr[0]])
		if ((s[arr[0]] == c && (s[arr[0] + 1] != c
						|| s[arr[0] + 1] != '\0')) || s[arr[0]] != c)
			++arr[1];
	if (!(result = (char**)malloc(sizeof(char*) * (arr[1] + 1))))
		return (0);
	arr[0] = -1;
	arr[2] = 0;
	arr[3] = 0;
	if (!write_words(s, c, arr, result))
		return (0);
	result[arr[2]] = 0;
	return (result);
}
