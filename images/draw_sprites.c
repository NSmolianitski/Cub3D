#include "cub_image.h"
#include <math.h>

static void	draw_sprites(t_all *all, t_draw_sprite sprite, t_tex_col tex_col, t_color color, const double z_buff[])
{
	int	stripe;
	int	y;

	stripe = sprite.d_start.x;
	while (stripe < sprite.d_end.x)
	{
		int texX = (int)(256 * (stripe - (-sprite.width / 2 + sprite.screen_x)) * tex_width / sprite.width) / 256;
		if (sprite.tf.y > 0 && stripe > 0 && stripe < all->pr->res_x && sprite.tf.y < z_buff[stripe])
		{
			y = sprite.d_start.y;
			while (y < sprite.d_end.y)
			{
				int d = (y) * 256 - all->pr->res_y * 128 + sprite.height * 128;
				int texY = ((d * tex_height) / sprite.height) / 256;
				color.walls = get_tex_color(tex_col.wall, texX, texY);
				if ((color.walls & 0x00ffffff) != 0)
					fast_mlx_pixel_put(all->win, stripe, y, color.walls);
				++y;
			}
		}
		++stripe;
	}
}

static void fill_sprite_prms(t_draw_sprite *sprite, t_all *all, const int order[], int i)
{
	sprite->x = all->pr->objs[order[i]].y - all->plr->y + 0.5;
	sprite->y = all->pr->objs[order[i]].x - all->plr->x + 0.5;
	sprite->depth = 1.0 / (all->plane.x * all->plr->dir.y - all->plr->dir.x * all->plane.y);
	sprite->tf.x = sprite->depth * (all->plr->dir.y * sprite->x - all->plr->dir.x * sprite->y);
	sprite->tf.y = sprite->depth * (-all->plane.y * sprite->x + all->plane.x * sprite->y);
	sprite->screen_x = (int)((all->pr->res_x / 2) * (1 + sprite->tf.x / sprite->tf.y));
	sprite->height = fabs((int)(all->pr->res_y / (sprite->tf.y)));
	sprite->d_start.y = -sprite->height / 2 + all->pr->res_y / 2;
	if (sprite->d_start.y < 0)
		sprite->d_start.y = 0;
}

void	count_draw_sprites(t_all *all, const double z_buff[], t_tex_col tex_col, t_color color)
{
	int				i;
	int				order[all->pr->objs_num];
	double			distance[all->pr->objs_num];
	t_draw_sprite	sprite;

	sort_sprites(distance, order, all->pr->objs_num, all);
	i = 0;
	while (i < all->pr->objs_num)
	{
		fill_sprite_prms(&sprite, all, order, i);
		sprite.d_end.y = sprite.height / 2 + all->pr->res_y / 2;
		if (sprite.d_end.y >= all->pr->res_y)
			sprite.d_end.y = all->pr->res_y - 1;
		sprite.width = fabs((int)(all->pr->res_y / (sprite.tf.y)));
		sprite.d_start.x = -sprite.width / 2 + sprite.screen_x;
		if (sprite.d_start.x < 0)
			sprite.d_start.x = 0;
		sprite.d_end.x = sprite.width / 2 + sprite.screen_x;
		if (sprite.d_end.x >= all->pr->res_x)
			sprite.d_end.x = all->pr->res_x - 1;
		tex_col.wall = &all->st;
		draw_sprites(all, sprite, tex_col, color, z_buff);
		++i;
	}
}
