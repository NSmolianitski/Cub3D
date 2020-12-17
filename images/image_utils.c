#include "cub_image.h"

void			fast_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char    *dst;

	dst = win->addr + (y * win->ll + x * (win->bpp / 8));
	*(unsigned int*)dst = color;
}

int	rgb_to_hex(int arr[3])
{
	return ((arr[0] & 0xff) << 16) + ((arr[1] & 0xff) << 8) + (arr[2] & 0xff);
}

void			draw_scaled_pixel(t_point *map, t_win img, int color)
{
	t_point		start;
	t_point		end;

	start.x = map->x * SCALE;
	start.y = map->y * SCALE;
	end.x = start.x + SCALE;
	end.y = start.y + SCALE;
	while (start.y < end.y)
	{
		start.x = map->x * SCALE;
		while (start.x < end.x)
		{
			fast_mlx_pixel_put(&img, start.x, start.y, color);
			++start.x;
		}
		++start.y;
	}
}

void			draw_player(t_player *player, t_win img, int color)
{
	t_point		start;
	t_point		end;

	start.x = player->x * SCALE;
	start.y = player->y * SCALE;
	end.x = start.x + (SCALE / 4);
	end.y = start.y + (SCALE / 4);
	while (start.y * SCALE < end.y * SCALE)
	{
		start.x = player->x * SCALE;
		while (start.x * SCALE < end.x * SCALE)
		{
			fast_mlx_pixel_put(&img, start.x, start.y, color);
			++start.x;
		}
		++start.y;
	}
}

void			draw_line(t_dpoint ray_end, int color, t_all *all, int len)
{
	t_dpoint	point;
	int			i;
	double		start_end_dist;

	i = 0;
	while (i < len)
	{
		start_end_dist = ((double)i / (double)len);
		point.x = all->plr->x + (ray_end.x - all->plr->x) * start_end_dist;
		point.y = all->plr->y + (ray_end.y - all->plr->y) * start_end_dist;
		++i;
		fast_mlx_pixel_put(all->win, point.x, point.y, color);
	}
}

void			draw_wall(t_dpoint start, t_dpoint ray_end, int color, t_all *all, int len)
{
	t_dpoint	point;
	int			i;
	double		start_end_dist;

	i = 0;
	while (i < len)
	{
		start_end_dist = ((double)i / (double)len);
		point.x = start.x + (ray_end.x - start.x) * start_end_dist;
		point.y = start.y + (ray_end.y - start.y) * start_end_dist;
		++i;
		if (point.y >= all->pr->res_y - 1|| point.x >= all->pr->res_x - 1)
			break ;
		for (int j = 0; j < (all->pr->res_x / 60); ++j)
			fast_mlx_pixel_put(all->win, point.x + j, point.y, color);
	}
}