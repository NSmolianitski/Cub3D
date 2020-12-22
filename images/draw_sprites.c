#include "cub_image.h"
#include <math.h>

static void	draw_sprites(t_all *all, t_ds s, t_tex_col tc, double z_buff[])
{
	int		stp;
	int		y;
	int		d;
	t_point	p;

	stp = s.d_start.x;
	while (stp < s.d_end.x)
	{
		p.x = (int)(256 * (stp - (-s.width / 2 + s.screen_x)) * TEX_W / s.width) / 256;
		if (s.tf.y > 0 && stp > 0 && stp < all->pr->res_x && s.tf.y < z_buff[stp])
		{
			y = s.d_start.y;
			while (y < s.d_end.y)
			{
				d = (y) * 256 - all->pr->res_y * 128 + s.height * 128;
				p.y = ((d * TEX_H) / s.height) / 256;
				tc.clr.walls = get_tex_color(tc.wall, p.x, p.y);
				if ((tc.clr.walls & 0x00ffffff) != 0)
					fast_mlx_pixel_put(all->win, stp, y, tc.clr.walls);
				++y;
			}
		}
		++stp;
	}
}

static void	fill_sprite_prms(t_ds *s, t_all *all, const int order[], int i)
{
	s->x = all->pr->objs[order[i]].y - all->plr->y + 0.5;
	s->y = all->pr->objs[order[i]].x - all->plr->x + 0.5;
	s->depth = 1.0 / (all->plane.x * all->plr->dir.y - all->plr->dir.x * all->plane.y);
	s->tf.x = s->depth * (all->plr->dir.y * s->x - all->plr->dir.x * s->y);
	s->tf.y = s->depth * (-all->plane.y * s->x + all->plane.x * s->y);
	s->screen_x = (int)((all->pr->res_x / 2) * (1 + s->tf.x / s->tf.y));
	s->height = fabs((float)(all->pr->res_y / (s->tf.y)));
	s->d_start.y = -s->height / 2 + all->pr->res_y / 2;
	if (s->d_start.y < 0)
		s->d_start.y = 0;
}

void		spr(t_all *all, double z_buff[], t_tex_col tex_col, t_color color)
{
	int				i;
	int				order[all->pr->objs_num];
	double			distance[all->pr->objs_num];
	t_ds			sprite;

	sort_sprites(distance, order, all->pr->objs_num, all);
	i = 0;
	while (i < all->pr->objs_num)
	{
		fill_sprite_prms(&sprite, all, order, i);
		sprite.d_end.y = sprite.height / 2 + all->pr->res_y / 2;
		if (sprite.d_end.y >= all->pr->res_y)
			sprite.d_end.y = all->pr->res_y - 1;
		sprite.width = fabs((float)(all->pr->res_y / (sprite.tf.y)));
		sprite.d_start.x = -sprite.width / 2 + sprite.screen_x;
		if (sprite.d_start.x < 0)
			sprite.d_start.x = 0;
		sprite.d_end.x = sprite.width / 2 + sprite.screen_x;
		if (sprite.d_end.x >= all->pr->res_x)
			sprite.d_end.x = all->pr->res_x - 1;
		tex_col.wall = &all->st;
		tex_col.clr = color;
		draw_sprites(all, sprite, tex_col, z_buff);
		++i;
	}
}
