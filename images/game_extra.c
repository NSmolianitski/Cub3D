#include <math.h>
#include "cub_image.h"
#include "libft.h"

static void	add_textures(t_all *all, t_ray_c *rc, int *side, t_tex_col *tc)
{
	if (*side == 0 && rc->step.x == -1)
		tc->wall = &all->nw;
	else if (*side == 0 && rc->step.x == 1)
		tc->wall = &all->sw;
	else if (*side == 1 && rc->step.y == 1)
		tc->wall = &all->ew;
	else if (*side == 1 && rc->step.y == -1)
		tc->wall = &all->ww;
}

static void	find_dist(int *side, t_ray_c *rc, t_all *all, t_tex_col *tex_col)
{
	int	hit;

	hit = 0;
	*side = 0;
	while (hit == 0)
	{
		if (rc->sd.x < rc->sd.y)
		{
			rc->sd.x += rc->dd.x;
			rc->map.x += rc->step.x;
			*side = 0;
		}
		else
		{
			rc->sd.y += rc->dd.y;
			rc->map.y += rc->step.y;
			*side = 1;
		}
		if (ft_strchr("1", all->pr->map[rc->map.x][rc->map.y]))
		{
			hit = 1;
			add_textures(all, rc, side, tex_col);
		}
	}
}

static void	check_direction(t_ray_c *rc, t_all *all)
{
	if (rc->rd.x < 0)
	{
		rc->step.x = -1;
		rc->sd.x = (all->plr->y - rc->map.x) * rc->dd.x;
	}
	else
	{
		rc->step.x = 1;
		rc->sd.x = (rc->map.x + 1.0 - all->plr->y) * rc->dd.x;
	}
	if (rc->rd.y < 0)
	{
		rc->step.y = -1;
		rc->sd.y = (all->plr->x - rc->map.y) * rc->dd.y;
	}
	else
	{
		rc->step.y = 1;
		rc->sd.y = (rc->map.y + 1.0 - all->plr->x) * rc->dd.y;
	}
}

void		ray_casting(t_all *all, t_color color)
{
	t_ray_c			rc;
	double			cam_x;
	t_tex_col		tc;
	double			z_buff[all->pr->res_x];
	int				x;

	x = 0;
	tc.clr = color;
	while (x < all->pr->res_x)
	{
		cam_x = 2 * x / (double)(all->pr->res_x - 1) - 1;
		rc.rd.x = all->plr->dir.x + all->plane.x * cam_x;
		rc.rd.y = all->plr->dir.y + all->plane.y * cam_x;
		rc.map.x = (int)(all->plr->y);
		rc.map.y = (int)(all->plr->x);
		rc.dd.x = sqrt(1 + (rc.rd.y * rc.rd.y) / (rc.rd.x * rc.rd.x));
		rc.dd.y = sqrt(1 + (rc.rd.x * rc.rd.x) / (rc.rd.y * rc.rd.y));
		check_direction(&rc, all);
		find_dist(&tc.wall_side, &rc, all, &tc);
		rc.x = x;
		draw_v_line(all, &rc, &tc, z_buff);
		++x;
	}
	spr(all, z_buff, tc, color);
}

void		draw_screen(t_all *all, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < all->pr->res_x)
	{
		y = 0;
		while (y < all->pr->res_y)
		{
			fast_mlx_pixel_put(all->win, x, y, color);
			++y;
		}
		++x;
	}
}