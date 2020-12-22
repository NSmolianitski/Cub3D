#include <math.h>
#include "libft.h"
#include "mlx.h"
#include "cub_parser.h"
#include "cub_image.h"
#include "cub_control.h"

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

static void	draw_v_line(t_all *all, t_ray_c *rc, t_tex_col *tc, double z_buff[])
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

static void	ray_casting(t_all *all, t_color color)
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

void		render_next_frame(t_all *all, int is_save, int flag)
{
	t_color color;

	if (flag)
		all->win->win = mlx_new_window(all->win->mlx, all->pr->res_x, all->pr->res_y, "Cub3D");
	mlx_clear_window(all->win->mlx, all->win->win);
	color.ceiling = rgb_to_hex(all->pr->ceilling_color);
	color.floor = rgb_to_hex(all->pr->floor_color);
	color.walls = 0x0104d3e;
	draw_screen(all, 0x0889bba);
	ray_casting(all, color);
	if (is_save)
	{
		create_bmp(all);
		exit(0);
	}
	else
		mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
}

static void	fill_txtrs(t_all *all, t_parser *parser)
{
	all->txtrs.n_wall = mlx_xpm_file_to_image(all->win->mlx, parser->n_wall, &all->txtrs.nw_prms.x, &all->txtrs.nw_prms.y);
	all->txtrs.s_wall = mlx_xpm_file_to_image(all->win->mlx, parser->so_wall, &all->txtrs.sw_prms.x, &all->txtrs.sw_prms.y);
	all->txtrs.s_wall = mlx_xpm_file_to_image(all->win->mlx, parser->s_wall, &all->txtrs.sw_prms.x, &all->txtrs.sw_prms.y);
	all->txtrs.w_wall = mlx_xpm_file_to_image(all->win->mlx, parser->w_wall, &all->txtrs.ww_prms.x, &all->txtrs.ww_prms.y);
	all->txtrs.e_wall = mlx_xpm_file_to_image(all->win->mlx, parser->e_wall, &all->txtrs.ew_prms.x, &all->txtrs.ew_prms.y);
	all->txtrs.sprite = mlx_xpm_file_to_image(all->win->mlx, parser->sprite, &all->txtrs.sprt_prms.x, &all->txtrs.sprt_prms.y);
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
	all->win->mlx = mlx_init();
	fill_txtrs(all, parser);
}

static void	fill_imgs(t_all *all)
{
	all->nw.img = all->txtrs.n_wall;
	all->nw.addr = mlx_get_data_addr(all->nw.img, &all->nw.bpp, &all->nw.ll, &all->nw.end);
	all->sw.img = all->txtrs.s_wall;
	all->sw.addr = mlx_get_data_addr(all->sw.img, &all->sw.bpp, &all->sw.ll, &all->sw.end);
	all->ww.img = all->txtrs.w_wall;
	all->ww.addr = mlx_get_data_addr(all->ww.img, &all->ww.bpp, &all->ww.ll, &all->ww.end);
	all->ew.img = all->txtrs.e_wall;
	all->ew.addr = mlx_get_data_addr(all->ew.img, &all->ew.bpp, &all->ew.ll, &all->ew.end);
	all->st.img = all->txtrs.sprite;
	all->st.addr = mlx_get_data_addr(all->st.img, &all->st.bpp, &all->st.ll, &all->st.end);
}

void		game(t_parser *parser, int is_save)
{
	t_win		win;
	t_player	player;
	t_all		all;
	int			flag;

	flag = 1;
	prepare_struct(&all, &win, &player, parser);
	win.img = mlx_new_image(all.win->mlx, parser->res_x, parser->res_y);
	win.addr = mlx_get_data_addr(win.img, &win.bpp, &win.ll, &win.end);
	fill_imgs(&all);
	render_next_frame(&all, is_save, flag);
	flag = 0;
	cub_control(&all);
	mlx_loop(all.win->mlx);
}