/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 13:54:42 by pkentaur          #+#    #+#             */
/*   Updated: 2020/10/31 14:37:11 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	checks(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (1);
	}
	else if (n == 0)
	{
		write(fd, "0", 1);
		return (1);
	}
	return (0);
}

void		ft_putnbr_fd(int n, int fd)
{
	char	arr[10];
	int		i;

	if (checks(n, fd))
		return ;
	else if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	i = 0;
	while (n != 0)
	{
		arr[i] = n % 10 + '0';
		n /= 10;
		++i;
	}
	--i;
	while (i >= 0)
	{
		write(fd, &arr[i], 1);
		--i;
	}
}
