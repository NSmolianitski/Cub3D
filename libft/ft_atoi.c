/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:26:29 by pkentaur          #+#    #+#             */
/*   Updated: 2020/11/03 12:11:21 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	space_number(const char *str)
{
	int		space_num;

	space_num = 0;
	while (str[space_num] == ' ' || (str[space_num] >= '\t' &&
				str[space_num] <= '\r'))
		++space_num;
	return (space_num);
}

static int	str_length(const char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
		++i;
	return (i);
}

static int	arrtoint(int arr_length, int i, int space_num, const char *str)
{
	int		k;
	int		j;
	int		arr[arr_length];
	int		l;

	k = i;
	j = 0;
	while (str[k + space_num] <= '9' && str[k + space_num] >= '0')
	{
		arr[j] = str[k + space_num] - '0';
		++k;
		++j;
	}
	k = 0;
	l = 0;
	while (l < j)
	{
		k = 10 * k + arr[l];
		++l;
	}
	return (k);
}

int			ft_atoi(const char *str)
{
	int		minus_num;
	int		i;
	int		s;
	int		j;

	j = str_length(str);
	minus_num = 0;
	i = 0;
	s = space_number(str);
	while (str[i + s] == ' ' || str[i + s] == '+' ||
			str[i + s] == '-' || (str[i + s] >= '\t' && str[i + s] <= '\r'))
	{
		if (str[i + s] == '-')
			++minus_num;
		if (str[i + s] == '+' && (str[i + s + 1] < '0' ||
					str[i + s + 1] > '9'))
			return (0);
		if (minus_num > 1 || (minus_num == 1 && str[i + s + 1] < '0'))
			return (0);
		++i;
	}
	i = arrtoint(j, i, s, str);
	if (minus_num % 2 != 0)
		i *= -1;
	return (i);
}
