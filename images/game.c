#include <math.h>
#include "mlx.h"
#include "cub_parser.h"
#include "cub_image.h"
#include "cub_control.h"

#define texWidth 64
#define texHeight 64

static void	draw_vert(int x, int drawStart, int drawEnd, t_all *all, t_color color)
{
	int		y;

	y = 0;
	while (y < drawStart)
	{
		fast_mlx_pixel_put(all->win, x, y, color.ceiling);
		++y;
	}
	while (drawStart <= drawEnd)
	{
		fast_mlx_pixel_put(all->win, x, drawStart, color.walls);
		++drawStart;
	}
	y = drawEnd + 1;
	while (y < all->pr->res_y)
	{
		fast_mlx_pixel_put(all->win, x, y, color.floor);
		++y;
	}
}

//RAY FROM PLAYER (POV)
static void	draw_pov(t_all *all, int color)
{
	t_dpoint start;
	t_dpoint end;

	start.x = all->plr->x;
	start.y = all->plr->y;
	end.x = all->plr->x + cos(all->plr->pov) * 30;
	end.y = all->plr->y + sin(all->plr->pov) * 30;
	draw_wall(start, end, color, all, 200);
}

static void	ray_casting(t_all *all, t_color color)
{
	t_ray_casting	rc;
	double			cameraX;
	double			wall_dist;
	int				hit;
	int				side;

	for(int x = 0; x < all->pr->res_x; x++)
	{
		cameraX = 2 * x / (double)(all->pr->res_x - 1) - 1;
		rc.ray_dir.x = all->plr->dir.x + all->plane.x * cameraX;
		rc.ray_dir.y = all->plr->dir.y + all->plane.y * cameraX;
		rc.map.x = (int)(all->plr->x);
		rc.map.y = (int)(all->plr->y);
		rc.delta_dist.x = sqrt(1 + (rc.ray_dir.y * rc.ray_dir.y) / (rc.ray_dir.x * rc.ray_dir.x));
		rc.delta_dist.y = sqrt(1 + (rc.ray_dir.x * rc.ray_dir.x) / (rc.ray_dir.y * rc.ray_dir.y));
		hit = 0;
		side = 0;
		if(rc.ray_dir.x < 0)
		{
			rc.step.x = -1;
			rc.side_dist.x = (all->plr->x - rc.map.x) * rc.delta_dist.x;
		}
		else
		{
			rc.step.x = 1;
			rc.side_dist.x = (rc.map.x + 1.0 - all->plr->x) * rc.delta_dist.x;
		}
		if(rc.ray_dir.y < 0)
		{
			rc.step.y = -1;
			rc.side_dist.y = (all->plr->y - rc.map.y) * rc.delta_dist.y;
		}
		else
		{
			rc.step.y = 1;
			rc.side_dist.y = (rc.map.y + 1.0 - all->plr->y) * rc.delta_dist.y;
		}
		while (hit == 0)
		{
			if (rc.side_dist.x < rc.side_dist.y)
			{
				rc.side_dist.x += rc.delta_dist.x;
				rc.map.x += rc.step.x;
				side = 0;
			}
			else
			{
				rc.side_dist.y += rc.delta_dist.y;
				rc.map.y += rc.step.y;
				side = 1;
			}
			if (all->pr->map[rc.map.x][rc.map.y] != '0')
				hit = 1;
		}
		if (side == 0)
			wall_dist = (rc.map.x - all->plr->x + (1 - rc.step.x) / 2) / rc.ray_dir.x;
		else
			wall_dist = (rc.map.y - all->plr->y + (1 - rc.step.y) / 2) / rc.ray_dir.y;
		int lineHeight = (int)(all->pr->res_y / wall_dist);
		int drawStart = -lineHeight / 2 + all->pr->res_y / 2;
		if (drawStart < 0)
			drawStart = 0;

		int drawEnd = lineHeight / 2 + all->pr->res_y / 2;
		if (drawEnd >= all->pr->res_y)
			drawEnd = all->pr->res_y - 1;
		//choose wall color
		color.walls = 0x0b81212; //red

		//give x and y sides different brightness
		if (side == 1)
			color.walls /= 2;

		//draw the pixels of the stripe as a vertical line
		draw_vert(x, drawStart, drawEnd, all, color);
	}
}

void draw_screen(t_all *all, int color)
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

void draw_rect(t_all *all, int left, int top, int width, int height, int color)
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

static void	draw_map(void *mlx, void *mlx_win, char **lvlmap, t_win win,
					 t_player *player, t_all *all)
{
	t_point	map;
	t_color color;

	color.ceiling = rgb_to_hex(all->pr->ceilling_color);
	color.floor = rgb_to_hex(all->pr->floor_color);
	color.walls = 0x02d2d2e;
	map.y = 0;
	draw_screen(all, 0x0889bba);
	color.walls = 0x0636391;
//	draw_cat(all, color.walls);
//	while (lvlmap[map.y])
//	{
//		map.x = 0;
//		while (lvlmap[map.y][map.x])
//		{
//			if (lvlmap[map.y][map.x] == '1')
//				draw_scaled_pixel(&map, win, 0x0042f66);
//			else if (lvlmap[map.y][map.x] == '2')
//				draw_scaled_pixel(&map, win, 0x0c0eb34);
//			else if (lvlmap[map.y][map.x] != ' ')
//				draw_scaled_pixel(&map, win, 0x02d2d2e);
//			++map.x;
//		}
//		++map.y;
//	}
//	draw_player(player, win, 0x0636391);
//	draw_pov(all, 0x0ff0000);
	ray_casting(all, color);
	mlx_put_image_to_window(mlx, mlx_win, win.img, 0, 0);
}

void	render_next_frame(t_all *all)
{
	mlx_clear_window(all->win->mlx, all->win->win);
	draw_map(all->win->mlx, all->win->win, all->pr->map, *all->win, all->plr, all);
}

static void prepare_struct(t_all *all, t_win *win, t_player *player, t_parser
*parser)
{
	all->win = win;
	all->plr = player;
	all->pr = parser;
	all->win->mlx = mlx_init();
}

void	game(t_parser *parser)
{
	t_win		win;
	t_player	player;
	t_all		all;

	player.x = 3;
	player.y = 3;
	player.pov = 1;
	player.dir.x = -1;
	player.dir.y = 0;
	all.plane.x = 0;
	all.plane.y = 0.66;

	t_point image;
	void *img;

	//Add params to all struct
	prepare_struct(&all, &win, &player, parser);
	//Mlx init
	win.img = mlx_new_image(all.win->mlx, parser->res_x, parser->res_y);
	win.addr = mlx_get_data_addr(win.img, &win.bpp, &win.ll, &win.end);
	win.win = mlx_new_window(all.win->mlx, parser->res_x, parser->res_y, "Cub3D");
//	Game draw
	render_next_frame(&all);
//	mlx_loop_hook(all.win->mlx, render_next_frame, &all);
//	Game control
	cub_control(&all);
	mlx_loop(all.win->mlx);
}