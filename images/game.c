#include <math.h>
#include "cub_utils.h"
#include "mlx.h"
#include "cub_parser.h"
#include "cub_image.h"
#include "cub_control.h"
#define P2 1.57079632679
#define P3 4.71238898038
#define DR 0.0174533

static void	draw_vert(int x, int drawStart, int drawEnd, t_all *all, t_color color, int wall_col)
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
		fast_mlx_pixel_put(all->win, x, drawStart, wall_col);
		++drawStart;
	}
	y = drawEnd + 1;
	while (y < all->pr->res_y)
	{
		fast_mlx_pixel_put(all->win, x, y, color.floor);
		++y;
	}
}

static double dist(t_dpoint a, t_dpoint b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

//LODEV
//static void	lodev(t_all *all, t_color color)
//{
//	int	x;
//
//	x = 0;
//	while (x < all->pr->res_x)
//	{
//		//calculate ray position and direction
//		double cameraX = 2 * x / (double)all->pr->res_x - 1; //x-coordinate in camera space
//		double rayDirX = all->plr->dir.x + all->plane.x * cameraX;
//		double rayDirY = all->plr->dir.y + all->plane.y * cameraX;
//		//which box of the map we're in
//		int mapX = (int)all->plr->y;
//		int mapY = (int)all->plr->x;
//
//		//length of ray from current position to next x or y-side
//		double sideDistX;
//		double sideDistY;
//
//		//length of ray from one x or y-side to next x or y-side
//		double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : cub_abs(1 / rayDirX));
//		double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : cub_abs(1 / rayDirY));
//		double perpWallDist;
//
//		//what direction to step in x or y-direction (either +1 or -1)
//		int stepX;
//		int stepY;
//
//		int hit = 0; //was there a wall hit?
//		int side; //was a NS or a EW wall hit?
//		//calculate step and initial sideDist
//		if (rayDirX < 0)
//		{
//			stepX = -1;
//			sideDistX = (all->plr->y - mapX) * deltaDistX;
//		} else
//		{
//			stepX = 1;
//			sideDistX = (mapX + 1.0 - all->plr->y) * deltaDistX;
//		}
//		if (rayDirY < 0)
//		{
//			stepY = -1;
//			sideDistY = (all->plr->x - mapY) * deltaDistY;
//		} else
//		{
//			stepY = 1;
//			sideDistY = (mapY + 1.0 - all->plr->x) * deltaDistY;
//		}
//		//perform DDA
//		while (hit == 0)
//		{
//			//jump to next map square, OR in x-direction, OR in y-direction
//			if (sideDistX < sideDistY)
//			{
//				sideDistX += deltaDistX;
//				mapX += stepX;
//				side = 0;
//			} else
//			{
//				sideDistY += deltaDistY;
//				mapY += stepY;
//				side = 1;
//			}
//			//Check if ray has hit a wall
//			if (all->pr->map[mapX][mapY] != '0') hit = 1;
//		}
//		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
//		if (side == 0) perpWallDist = (mapX - all->plr->y + (1 - stepX) / 2) / rayDirX;
//		else perpWallDist = (mapY - all->plr->x + (1 - stepY) / 2) / rayDirY;
//
//		//Calculate height of line to draw on screen
//		int lineHeight = (int) (2 * all->pr->res_y / perpWallDist);
//
//		//calculate lowest and highest pixel to fill in current stripe
//		int drawStart = -lineHeight / 2 + all->pr->res_y / 2;
//		if (drawStart < 0)drawStart = 0;
//		int drawEnd = lineHeight / 2 + all->pr->res_y / 2;
//		if (drawEnd >= all->pr->res_y)drawEnd = all->pr->res_y - 1;
//
//		//give x and y sides different brightness
//		if (side == 1)
//			draw_vert(x, drawStart, drawEnd, all, color,  color.walls /1.5);
//		else
//			draw_vert(x, drawStart, drawEnd, all, color, color.walls);
//		++x;
//	}
//}

int mapa[] =
		{ 1,1,1,1,1,1,1,1,
	      1,0,1,0,0,0,0,1,
	      1,0,1,0,0,1,0,1,
	      1,0,1,0,0,0,0,1,
	      1,0,0,0,0,0,0,1,
	      1,0,0,0,0,0,0,1,
	      1,0,0,0,0,0,0,1,
	      1,1,1,1,1,1,1,1,
		};

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

int mapX = 8;
int mapY = 8;
int mapS = 64;

static void draw_cat(t_all *all, int color)
{
	int r, mx, my, mp, dof;
	double rx, ry, ra, xo, yo, distT;
	t_dpoint horizontal;
	t_dpoint vertical;
	t_dpoint player;

	ra = all->plr->pov - DR * 30;
	if (ra < 0)
		ra += 2 * M_PI;
	else if (ra > 2 * M_PI)
		ra -= 2 * M_PI;
	for (r = 0; r < 60; ++r)
	{
//		//Horizontal lines
		dof = 0;
		double distH = 1000000;
		horizontal.x = all->plr->x;
		horizontal.y = all->plr->y;
		double aTan = -1 / tan(ra);
		if (ra > M_PI)
		{
			ry = (((int)all->plr->y / SCALE) * SCALE) - 0.0001;
			rx = (all->plr->y - ry) * aTan + all->plr->x;
			yo = -SCALE;
			xo = -yo * aTan;
		}
		else if (ra < M_PI)
		{
			ry = (((int)all->plr->y / SCALE) * SCALE) + SCALE;
			rx = (all->plr->y - ry) * aTan + all->plr->x;
			yo = SCALE;
			xo = -yo * aTan;
		}
		else if (ra == 0 || ra == M_PI)
		{
			rx = all->plr->x;
			ry = all->plr->y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) / SCALE;
			my = (int)(ry) / SCALE;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && mapa[mp] == 1)
			{
				horizontal.x = rx;
				horizontal.y = ry;
				player.x = all->plr->x;
				player.y = all->plr->y;
				distH = dist(player, horizontal);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				++dof;
			}
		}
		t_dpoint ray;
		ray.x = rx;
		ray.y = ry;

		//Vertical lines
		dof = 0;
		double distV = 1000000;
		vertical.x = all->plr->x;
		vertical.y = all->plr->y;
		double nTan = -tan(ra);
		if (ra > P2 && ra < P3)
		{
			rx = (((int)all->plr->x / SCALE) * SCALE) - 0.0001;
			ry = (all->plr->x - rx) * nTan + all->plr->y;
			xo = -SCALE;
			yo = -xo * nTan;
		}
		else if (ra < P2 || ra > P3)
		{
			rx = (((int)all->plr->x / SCALE) * SCALE) + SCALE;
			ry = (all->plr->x - rx) * nTan + all->plr->y;
			xo = SCALE;
			yo = -xo * nTan;
		}
		else if (ra == 0 || ra == M_PI)
		{
			rx = all->plr->x;
			ry = all->plr->y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) / SCALE;
			my = (int)(ry) / SCALE;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && mapa[mp] == 1)
			{
				vertical.x = rx;
				vertical.y = ry;
				player.x = all->plr->x;
				player.y = all->plr->y;
				distV = dist(player, vertical);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				++dof;
			}
		}
		t_dpoint raye;
		if (distV < distH)
		{
			raye.x = vertical.x;
			raye.y = vertical.y;
			distT = distV;
		}
		else if (distH < distV)
		{
			raye.x = horizontal.x;
			raye.y = horizontal.y;
			distT = distH;
		}
		draw_line(raye, color, all, 500);
		//3D Walls
		double ca = all->plr->pov - ra;
		if (ca < 0)
			ca += 2 * M_PI;
		else if (ca > 2 * M_PI)
			ca -= 2 * M_PI;
		distT *= cos(ca);
		double lineH = (SCALE * all->pr->res_x / 2) / distT;
		if (lineH > all->pr->res_x / 2)
			lineH = all->pr->res_x / 2;
		double lineO = all->pr->res_x / 4 - lineH / 2;
		raye.x = r * (all->pr->res_x / 60);
		raye.y = lineO;
		t_dpoint end;
		end.x = r * (all->pr->res_x / 60);
		end.y = lineH + lineO;
		if (distV < distH)
			draw_wall(raye, end, color - 200, all, 500);
		else if (distV > distH)
			draw_wall(raye, end, color, all, 500);
		ra += DR;
		if (ra < 0)
			ra += 2 * M_PI;
		else if (ra > 2 * M_PI)
			ra -= 2 * M_PI;
	}
}

static void	draw_screen(t_all *all, t_color color)
{
	int	x;

	while (x < all->pr->res_x)
	{
		draw_vert(x, 0, all->pr->res_y - 1, all, color, 0x02d2d2e);
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
	color.walls = 0x0636391;
//	lodev(all, color);
	map.y = 0;
	draw_screen(all, color);
	while (lvlmap[map.y])
	{
		map.x = 0;
		while (lvlmap[map.y][map.x])
		{
			if (lvlmap[map.y][map.x] == '1')
				draw_scaled_pixel(&map, win, 0x0042f66);
			else if (lvlmap[map.y][map.x] == '2')
				draw_scaled_pixel(&map, win, 0x0c0eb34);
			else if (lvlmap[map.y][map.x] != ' ')
				draw_scaled_pixel(&map, win, 0x02d2d2e);
			++map.x;
		}
		++map.y;
	}
	draw_player(player, win, 0x0636391);
	draw_cat(all, color.walls);
	draw_pov(all, 0x0ff0000);
	mlx_put_image_to_window(mlx, mlx_win, win.img, 0, 0);
}

int     render_next_frame(t_all *all)
{
	mlx_clear_window(all->win->mlx, all->win->win);
	draw_map(all->win->mlx, all->win->win, all->pr->map, *all->win, all->plr,
		  all);
	return(1);
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

	player.x = 3 * SCALE;
	player.y = 3 * SCALE;
	player.pov = 4;
	player.dir.x = -1;
	player.dir.y = 0;
	all.plane.x = 0;
	all.plane.y = 0.66;

	//Add params to all struct
	prepare_struct(&all, &win, &player, parser);
	//Mlx init
	win.img = mlx_new_image(all.win->mlx, parser->res_x, parser->res_y);
	win.addr = mlx_get_data_addr(win.img, &win.bpp, &win.ll, &win.end);
	win.win = mlx_new_window(all.win->mlx, parser->res_x, parser->res_y, "Cub3D");
	//Game draw
	mlx_loop_hook(all.win->mlx, render_next_frame, &all);
	//Game control
	cub_control(&all);
	mlx_loop(all.win->mlx);
}