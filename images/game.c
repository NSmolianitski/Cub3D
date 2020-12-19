#include <math.h>
#include "libft.h"
#include "mlx.h"
#include "cub_parser.h"
#include "cub_image.h"
#include "cub_control.h"

#define texWidth 64
#define texHeight 64

t_win	nwall;
t_win	swall;
t_win	wwall;
t_win	ewall;
t_win	stex;

//arrays used to sort the sprites
//function used to sort the sprites
//void sortSprites(int* order, double* dist, int amount)
//{
//	std::vector<std::pair<double, int>> sprites(amount);
//	for(int i = 0; i < amount; i++) {
//		sprites[i].first = dist[i];
//		sprites[i].second = order[i];
//	}
//	std::sort(sprites.begin(), sprites.end());
//	// restore in reverse order to go from farthest to nearest
//	for(int i = 0; i < amount; i++) {
//		dist[i] = sprites[amount - i - 1].first;
//		order[i] = sprites[amount - i - 1].second;
//	}
//}
//}

static void	draw_vert(int x, int draw_start, int draw_end, t_all *all, t_color color, t_tex_col *tex_col)
{
	int		y;

	y = 0;
	while (y < draw_start)
	{
		fast_mlx_pixel_put(all->win, x, y, color.ceiling);
		++y;
	}
	while (draw_start <= draw_end)
	{
		tex_col->tex_y = (int)tex_col->tex_pos & (texHeight - 1);
		tex_col->tex_pos += tex_col->tex_step;
		color.walls = get_tex_color(tex_col->wall, tex_col->tex_x, tex_col->tex_y);
		if (tex_col->wall_side == 1)
			color.walls = (color.walls >> 1) & 8355711;
		fast_mlx_pixel_put(all->win, x, draw_start, color.walls);
		++draw_start;
	}
	y = draw_end + 1;
	while (y < all->pr->res_y)
	{
		fast_mlx_pixel_put(all->win, x, y, color.floor);
		++y;
	}
}

static void	draw_vertical_line(t_all *all, t_ray_casting *rc, int x, t_color color, int side, t_tex_col *tex_col, double ZBuffer[])
{
	double		wall_dist;
	int			draw_start;
	int			draw_end;
	int			lineHeight;
	double		wall_x;

	if (side == 0)
		wall_dist = (rc->map.x - all->plr->y + (1 - rc->step.x) / 2) / rc->ray_dir.x;
	else
		wall_dist = (rc->map.y - all->plr->x + (1 - rc->step.y) / 2) / rc->ray_dir.y;
	lineHeight = (int)(all->pr->res_y / wall_dist);
	draw_start = -lineHeight / 2 + all->pr->res_y / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = lineHeight / 2 + all->pr->res_y / 2;
	if (draw_end >= all->pr->res_y)
		draw_end = all->pr->res_y - 1;
	if (side == 0)
		wall_x = all->plr->x + wall_dist * rc->ray_dir.y;
	else
		wall_x = all->plr->y + wall_dist * rc->ray_dir.x;
	wall_x -= floor(wall_x);
	tex_col->tex_x = (int)(wall_x * (double)(texWidth));
	if (side == 0 && rc->ray_dir.x > 0)
		tex_col->tex_x = texWidth - tex_col->tex_x - 1;
	if (side == 1 && rc->ray_dir.y < 0)
		tex_col->tex_x = texWidth - tex_col->tex_x - 1;
	tex_col->wall_side = side;
	tex_col->tex_step = 1.0 * texHeight / lineHeight;
	// Starting texture coordinate
	tex_col->tex_pos = (draw_start - all->pr->res_y / 2 + lineHeight / 2) * tex_col->tex_step;
	draw_vert(x, draw_start, draw_end, all, color, tex_col);

	ZBuffer[x] = wall_dist;

}

static void	find_dist(int *side, t_ray_casting *rc, t_all *all, t_tex_col *tex_col)
{
	int	hit;

	hit = 0;
	*side = 0;
	while (hit == 0)
	{
		if (rc->side_dist.x < rc->side_dist.y)
		{
			rc->side_dist.x += rc->delta_dist.x;
			rc->map.x += rc->step.x;
			*side = 0;
		}
		else
		{
			rc->side_dist.y += rc->delta_dist.y;
			rc->map.y += rc->step.y;
			*side = 1;

		}
		if (ft_strchr("1", all->pr->map[rc->map.x][rc->map.y]))
		{
			hit = 1;
			if (*side == 0 && rc->step.x == -1)
				tex_col->wall = &nwall;
			else if (*side == 0 && rc->step.x == 1)
				tex_col->wall = &swall;
			else if (*side == 1 && rc->step.y == 1)
				tex_col->wall = &ewall;
			else if (*side == 1 && rc->step.y == -1)
				tex_col->wall = &wwall;
		}
	}
}

static void	check_direction(t_ray_casting *rc, t_all *all, t_tex_col *tex_col)
{
	if(rc->ray_dir.x < 0)
	{
		rc->step.x = -1;
		rc->side_dist.x = (all->plr->y - rc->map.x) * rc->delta_dist.x;
	}
	else
	{
		rc->step.x = 1;
		rc->side_dist.x = (rc->map.x + 1.0 - all->plr->y) * rc->delta_dist.x;
	}
	if(rc->ray_dir.y < 0)
	{
		rc->step.y = -1;
		rc->side_dist.y = (all->plr->x - rc->map.y) * rc->delta_dist.y;
	}
	else
	{
		rc->step.y = 1;
		rc->side_dist.y = (rc->map.y + 1.0 - all->plr->x) * rc->delta_dist.y;
	}
}

static void	ray_casting(t_all *all, t_color color)
{
	t_ray_casting	rc;
	double			cameraX;
	t_tex_col		tex_col;
	double			ZBuffer[all->pr->res_x];
	int spriteOrder[all->pr->objs_num];
	double spriteDistance[all->pr->objs_num];

	for(int x = 0; x < all->pr->res_x; x++)
	{
		cameraX = 2 * x / (double)(all->pr->res_x - 1) - 1;
		rc.ray_dir.x = all->plr->dir.x + all->plane.x * cameraX;
		rc.ray_dir.y = all->plr->dir.y + all->plane.y * cameraX;
		rc.map.x = (int)(all->plr->y);
		rc.map.y = (int)(all->plr->x);
		rc.delta_dist.x = sqrt(1 + (rc.ray_dir.y * rc.ray_dir.y) / (rc.ray_dir.x * rc.ray_dir.x));
		rc.delta_dist.y = sqrt(1 + (rc.ray_dir.x * rc.ray_dir.x) / (rc.ray_dir.y * rc.ray_dir.y));
		check_direction(&rc, all, &tex_col);
		find_dist(&tex_col.wall_side, &rc, all, &tex_col);
		draw_vertical_line(all, &rc, x, color, tex_col.wall_side, &tex_col, ZBuffer);
	}
	//SPRITE CASTING
	//sort sprites from far to close
	for(int i = 0; i < all->pr->objs_num; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((all->plr->x - all->pr->objs[i].x) * (all->plr->x - all->pr->objs[i].x) + (all->plr->y - all->pr->objs[i].y) * (all->plr->y - all->pr->objs[i].y)); //sqrt not taken, unneeded
	}
//	sortSprites(spriteOrder, spriteDistance, numSprites);

	//after sorting the sprites, do the projection and draw them
	for(int i = 0; i < all->pr->objs_num; i++)
	{
		//translate sprite position to relative to camera
		double spriteX = all->pr->objs[spriteOrder[i]].x - all->plr->y;
		double spriteY = all->pr->objs[spriteOrder[i]].y - all->plr->x;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (all->plane.x * all->plr->dir.y - all->plr->dir.x * all->plane.y); //required for correct matrix multiplication

		double transformX = invDet * (all->plr->dir.y * spriteX - all->plr->dir.x * spriteY);
		double transformY = invDet * (-all->plane.y * spriteX + all->plane.x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = (int)((all->pr->res_x / 2) * (1 + transformX / transformY));

		//calculate height of the sprite on screen
		int spriteHeight = fabs((int)(all->pr->res_y / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + all->pr->res_y / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + all->pr->res_y / 2;
		if (drawEndY >= all->pr->res_y)
			drawEndY = all->pr->res_y - 1;

		//calculate width of the sprite
		int spriteWidth = abs( (int) (all->pr->res_y / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= all->pr->res_x)
			drawEndX = all->pr->res_x - 1;
		tex_col.wall = &stex;
		//loop through every vertical stripe of the sprite on screen
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < all->pr->res_x && transformY < ZBuffer[stripe])
			{
				for (int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = (y) * 256 - all->pr->res_y * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * texHeight) / spriteHeight) / 256;
					color.walls = get_tex_color(tex_col.wall, texX, texY);
					if ((color.walls & 0x00FFFFFF) != 0)
						fast_mlx_pixel_put(all->win, stripe, y, color.walls); //paint pixel if it isn't black, black is the invisible color
				}
			}
		}
	}
}

void		draw_screen(t_all *all, int color)
{
	int x, y;

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

void		draw_rect(t_all *all, int left, int top, int width, int height, int color)
{
	int x;
	int y;

	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			fast_mlx_pixel_put(all->win, left + x, top + y, color);
			++y;
		}
		++x;
	}
}

static void	draw_map(t_all *all)
{
	t_point	map;

	map.y = 0;
	while (all->pr->map[map.y])
	{
		map.x = 0;
		while (all->pr->map[map.y][map.x])
		{
			if (all->pr->map[map.y][map.x] == '1')
				draw_scaled_pixel(&map, *all->win, 0x0042f66);
			else if (all->pr->map[map.y][map.x] == '2')
				draw_scaled_pixel(&map, *all->win, 0x0c0eb34);
			else if (all->pr->map[map.y][map.x] != ' ')
				draw_scaled_pixel(&map, *all->win, 0x02d2d2e);
			++map.x;
		}
		++map.y;
	}
}

static void	draw_game(t_all *all)
{
	t_color color;

	color.ceiling = rgb_to_hex(all->pr->ceilling_color);
	color.floor = rgb_to_hex(all->pr->floor_color);
	color.walls = 0x0104d3e;
	draw_screen(all, 0x0889bba);
	ray_casting(all, color);
//	draw_map(all);
//	draw_player(all->plr, *all->win, 0x0636391);
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
}

void		render_next_frame(t_all *all)
{
	mlx_clear_window(all->win->mlx, all->win->win);
	draw_game(all);
}

static void	prepare_struct(t_all *all, t_win *win, t_player *player, t_parser *parser)
{
	all->win = win;
	all->plr = player;
	all->pr = parser;
	all->plr->y = parser->player_pos.y + 0.5;
	all->plr->x = parser->player_pos.x + 0.5;
	all->plr->dir.x = -1;
	all->plr->dir.y = 0;
	all->plane.x = 0;
	all->plane.y = 0.66;
	if (all->pr->player_dir == 'W')
		rotation(0, all, -M_PI / 2);
	else if (all->pr->player_dir == 'N')
		all->plr->dir.x = -1;
	else if (all->pr->player_dir == 'E')
		rotation(2, all, M_PI / 2);
	else if (all->pr->player_dir == 'S')
		rotation(0, all, M_PI);
	all->txtrs = malloc(sizeof(t_textures));
	all->txtrs->n_wall = mlx_xpm_file_to_image(all->win->mlx, parser->n_wall, &all->txtrs->nw_prms.x, &all->txtrs->nw_prms.y);
	all->txtrs->s_wall = mlx_xpm_file_to_image(all->win->mlx, parser->so_wall, &all->txtrs->sw_prms.x, &all->txtrs->sw_prms.y);
	all->txtrs->s_wall = mlx_xpm_file_to_image(all->win->mlx, parser->s_wall, &all->txtrs->sw_prms.x, &all->txtrs->sw_prms.y);
	all->txtrs->w_wall = mlx_xpm_file_to_image(all->win->mlx, parser->w_wall, &all->txtrs->ww_prms.x, &all->txtrs->ww_prms.y);
	all->txtrs->e_wall = mlx_xpm_file_to_image(all->win->mlx, parser->e_wall, &all->txtrs->ew_prms.x, &all->txtrs->ew_prms.y);
	all->txtrs->sprite = mlx_xpm_file_to_image(all->win->mlx, parser->sprite, &all->txtrs->sprt_prms.x, &all->txtrs->sprt_prms.y);
	all->win->mlx = mlx_init();
}


void		game(t_parser *parser)
{
	t_win		win;
	t_player	player;
	t_all		all;

	prepare_struct(&all, &win, &player, parser);
	//Mlx init
	win.img = mlx_new_image(all.win->mlx, parser->res_x, parser->res_y);
	win.addr = mlx_get_data_addr(win.img, &win.bpp, &win.ll, &win.end);
	win.win = mlx_new_window(all.win->mlx, parser->res_x, parser->res_y, "Cub3D");
		//Game draw
	nwall.img = all.txtrs->n_wall;
	nwall.addr = mlx_get_data_addr(nwall.img, &nwall.bpp, &nwall.ll, &nwall.end);
	swall.img = all.txtrs->s_wall;
	swall.addr = mlx_get_data_addr(swall.img, &swall.bpp, &swall.ll, &swall.end);
	wwall.img = all.txtrs->w_wall;
	wwall.addr = mlx_get_data_addr(wwall.img, &wwall.bpp, &wwall.ll, &wwall.end);
	ewall.img = all.txtrs->e_wall;
	ewall.addr = mlx_get_data_addr(ewall.img, &ewall.bpp, &ewall.ll, &ewall.end);
	stex.img = all.txtrs->sprite;
	stex.addr = mlx_get_data_addr(stex.img, &stex.bpp, &stex.ll, &stex.end);
	render_next_frame(&all);
	//Game control
	cub_control(&all);
	mlx_loop(all.win->mlx);
}