/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:39:25 by pkentaur          #+#    #+#             */
/*   Updated: 2020/12/22 15:39:31 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "cub_image.h"
#include "libft.h"

static void		write_image(t_bmp *bmp, unsigned char *colors, int size)
{
	int	fd;

	fd = open("1.bmp", O_RDWR | O_CREAT, 0755);
	write(fd, bmp, sizeof(*bmp));
	write(fd, colors, size);
	free(colors);
	close(fd);
}

static void		fill_colors(t_all *all, t_bmp *bmp, int width, int height)
{
	int				y;
	int				x;
	unsigned char	*colors;
	int				size;
	int				i;

	i = 0;
	size = width * height * 4;
	colors = malloc(size);
	y = height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < width)
		{
			colors[i + 0] = get_tex_color(all->win, x, y) & 0xFF;
			colors[i + 1] = (get_tex_color(all->win, x, y) >> 8) & 0xFF;
			colors[i + 2] = (get_tex_color(all->win, x, y) >> 16) & 0xFF;
			++x;
			i += 4;
		}
		--y;
	}
	write_image(bmp, colors, size);
}

static void		fill_bmp_header(t_all *all, int width, int height)
{
	int				size;
	t_bmp			bmp;

	size = width * height * 4;
	ft_strlcpy((char *)&bmp.type, "BM", 3);
	bmp.size = 54 + size;
	bmp.res = 0;
	bmp.res2 = 0;
	bmp.offset = 54;
	bmp.h_size = 40;
	bmp.width = width;
	bmp.height = height;
	bmp.planes = 1;
	bmp.bpp = 32;
	bmp.compression = 0;
	bmp.i_size = size;
	bmp.ppm_x = 0;
	bmp.ppm_y = 0;
	bmp.clrs = 0;
	bmp.clrs_imp = 0;
	fill_colors(all, &bmp, width, height);
}

void			create_bmp(t_all *all)
{
	fill_bmp_header(all, all->pr->res_x, all->pr->res_y);
}
