#include <math.h>
#include "libft.h"
#include "mlx.h"
#include "cub_parser.h"
#include "cub_image.h"
#include "cub_control.h"

#define texWidth 64
#define texHeight 64
t_win	nwall;
static void	draw_vert(int x, int draw_start, int draw_end, t_all *all, t_color color, t_tex_col tex_col)
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
		tex_col.tex_y = (int)tex_col.tex_pos & (texHeight - 1);
		tex_col.tex_pos += tex_col.tex_step;
		color.walls = get_tex_color(nwall, tex_col.tex_x, tex_col.tex_y);
		if(tex_col.wall_side == 1)
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

static void	draw_vertical_line(t_all *all, t_ray_casting *rc, int x, t_color color, int side)
{
	double		wall_dist;
	int			draw_start;
	int			draw_end;
	int			lineHeight;
	t_tex_col	tex_col;
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
	if (side == 0) wall_x = all->plr->x + wall_dist * rc->ray_dir.y;
	else           wall_x = all->plr->y + wall_dist * rc->ray_dir.x;
	wall_x -= floor(wall_x);
	tex_col.tex_x = (int)(wall_x * (double)(texWidth));
	if (side == 0 && rc->ray_dir.x > 0)
		tex_col.tex_x = texWidth - tex_col.tex_x - 1;
	if (side == 1 && rc->ray_dir.y < 0)
		tex_col.tex_x = texWidth - tex_col.tex_x - 1;
	tex_col.wall_side = side;
	tex_col.tex_step = 1.0 * texHeight / lineHeight;
	// Starting texture coordinate
	tex_col.tex_pos = (draw_start - all->pr->res_y / 2 + lineHeight / 2) * tex_col.tex_step;
	draw_vert(x, draw_start, draw_end, all, color, tex_col);
}

static void	find_dist(int *side, t_ray_casting *rc, t_all *all)
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
		if (ft_strchr("12", all->pr->map[rc->map.x][rc->map.y]))
			hit = 1;
	}
}

static void	check_direction(t_ray_casting *rc, t_all *all)
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
	int				side;

	for(int x = 0; x < all->pr->res_x; x++)
	{
		cameraX = 2 * x / (double)(all->pr->res_x - 1) - 1;
		rc.ray_dir.x = all->plr->dir.x + all->plane.x * cameraX;
		rc.ray_dir.y = all->plr->dir.y + all->plane.y * cameraX;
		rc.map.x = (int)(all->plr->y);
		rc.map.y = (int)(all->plr->x);
		rc.delta_dist.x = sqrt(1 + (rc.ray_dir.y * rc.ray_dir.y) / (rc.ray_dir.x * rc.ray_dir.x));
		rc.delta_dist.y = sqrt(1 + (rc.ray_dir.x * rc.ray_dir.x) / (rc.ray_dir.y * rc.ray_dir.y));
		check_direction(&rc, all);
		find_dist(&side, &rc, all);
		draw_vertical_line(all, &rc, x, color, side);
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
	draw_map(all);
	draw_player(all->plr, *all->win, 0x0636391);
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
		rotation(0, all, 1.57);
	else if (all->pr->player_dir == 'N')
		all->plr->dir.x = -1;
	else if (all->pr->player_dir == 'E')
		rotation(2, all, 1.57);
	else if (all->pr->player_dir == 'S')
		rotation(0, all, 3.14);
	all->txtrs = malloc(sizeof(t_textures));
	all->txtrs->n_wall = mlx_xpm_file_to_image(all->win->mlx, parser->n_wall, &all->txtrs->nw_prms.x, &all->txtrs->nw_prms.y);
	all->txtrs->s_wall = mlx_xpm_file_to_image(all->win->mlx, parser->n_wall, &all->txtrs->sw_prms.x, &all->txtrs->sw_prms.y);
	all->txtrs->w_wall = mlx_xpm_file_to_image(all->win->mlx, parser->n_wall, &all->txtrs->ww_prms.x, &all->txtrs->ww_prms.y);
	all->txtrs->e_wall = mlx_xpm_file_to_image(all->win->mlx, parser->n_wall, &all->txtrs->ew_prms.x, &all->txtrs->ew_prms.y);
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
	render_next_frame(&all);
	//Game control
	cub_control(&all);
	mlx_loop(all.win->mlx);
}