/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:42:51 by pkentaur          #+#    #+#             */
/*   Updated: 2020/12/22 15:43:05 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub_image.h"

static void	draw_vert(int x, t_draw draw, t_all *all, t_tex_col *tc)
{
	int		y;

	y = 0;
	while (y < draw.s)
	{
		fast_mlx_pixel_put(all->win, x, y, tc->clr.ceiling);
		++y;
	}
	while (draw.s <= draw.e)
	{
		tc->tex_y = (int)tc->tex_pos & (TEX_H - 1);
		tc->tex_pos += tc->tex_step;
		tc->clr.walls = get_tex_color(tc->wall, tc->tex_x, tc->tex_y);
		if (tc->wall_side == 1)
			tc->clr.walls = (tc->clr.walls >> 1) & 8355711;
		fast_mlx_pixel_put(all->win, x, draw.s, tc->clr.walls);
		++draw.s;
	}
	y = draw.e + 1;
	while (y < all->pr->res_y)
	{
		fast_mlx_pixel_put(all->win, x, y, tc->clr.floor);
		++y;
	}
}

static void	fill_tc(t_tex_col *tc, t_ray_c *rc, double wall_x, int line_h)
{
	wall_x -= floor(wall_x);
	tc->tex_x = (int)(wall_x * (double)(TEX_W));
	if (tc->wall_side == 0 && rc->rd.x > 0)
		tc->tex_x = TEX_W - tc->tex_x - 1;
	if (tc->wall_side == 1 && rc->rd.y < 0)
		tc->tex_x = TEX_W - tc->tex_x - 1;
	tc->tex_step = 1.0 * TEX_H / line_h;
}

void		draw_v_line(t_all *all, t_ray_c *rc, t_tex_col *tc, double z_buff[])
{
	double		wd;
	t_draw		draw;
	int			line_h;
	double		wall_x;

	if (tc->wall_side == 0)
		wd = (rc->map.x - all->plr->y + (1 - rc->step.x) / 2) / rc->rd.x;
	else
		wd = (rc->map.y - all->plr->x + (1 - rc->step.y) / 2) / rc->rd.y;
	line_h = (int)(all->pr->res_y / wd);
	draw.s = -line_h / 2 + all->pr->res_y / 2;
	if (draw.s < 0)
		draw.s = 0;
	draw.e = line_h / 2 + all->pr->res_y / 2;
	if (draw.e >= all->pr->res_y)
		draw.e = all->pr->res_y - 1;
	if (tc->wall_side == 0)
		wall_x = all->plr->x + wd * rc->rd.y;
	else
		wall_x = all->plr->y + wd * rc->rd.x;
	fill_tc(tc, rc, wall_x, line_h);
	tc->tex_pos = (draw.s - all->pr->res_y / 2 + line_h / 2) * tc->tex_step;
	draw_vert(rc->x, draw, all, tc);
	z_buff[rc->x] = wd;
}
